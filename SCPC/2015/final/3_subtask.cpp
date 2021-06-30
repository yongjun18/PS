#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Edge{
	int from, to, w;
	int used, incycle;
	bool operator < (const Edge& rhs) const{
		return w > rhs.w;
	}
};

vector<Edge> adj[105];
vector< vector<Edge> > cycle;
int otsum;
int visit[105];
vector<Edge> st;
int cnt;
int dfsn[105];

void dfs(int now, int par){
	dfsn[now] = cnt++;
	for (Edge &e : adj[now]){
		if (e.to == par) continue;
		e.used = 1;

		if (visit[e.to] == 0){
			st.push_back(e);
			otsum += e.w;
			visit[e.to] = 1;
			dfs(e.to, now);
			st.pop_back();
		}
		else if (dfsn[now] > dfsn[e.to]){
			vector<Edge> newc;
			newc.push_back(e);
			e.incycle = 1;
			for (auto it = st.rbegin();; it++){
				newc.push_back(*it);
				otsum -= it->w;
				//it->incycle = 1;
				for (auto& it2 : adj[it->from]){
					if (it2.to == it->to){
						it2.incycle = 1;
					}
				}
				if (it->from == e.to) break;
			}
			sort(newc.begin(), newc.end());
			cycle.push_back(newc);
		}
	}
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		int bneck;
		ll ans1, ans2;
		scanf("%d %d", &n, &m);

		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
			visit[i] = 0;
		}
		cycle.clear();
		otsum = 0;
		cnt = 0;
		st.clear();

		while (m--){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			adj[u].push_back({ u, v, w, 0, 0 });
			adj[v].push_back({ v, u, w, 0, 0 });
		}
		visit[1] = 1;
		dfs(1, -1);

		ans1 = 1;
		ans2 = 1;
		for (auto &it : cycle){
			int maxcnt = 1;
			for (int i = 1; i < it.size(); i++){
				if (it[0].w != it[i].w) break;
				maxcnt++;
			}
			ans1 *= maxcnt;
			ans1 %= MOD;
		}

		bneck = -1;
		for (int i = 1; i <= n; i++){
			for (Edge& e : adj[i]){
				if (e.used == 1 && e.incycle == 0){
					bneck = max(bneck, e.w);
				}
			}
		}
		for (auto &it : cycle){
			bneck = max(bneck, it[1].w);
		}
		for (auto &it : cycle){
			if (it[0].w > bneck) continue;
			ans2 *= it.size();
			ans2 %= MOD;
		}

		printf("Case #%d\n", test);
		printf("%lld %lld\n", ans1, ans2);
	}

	return 0;
}
