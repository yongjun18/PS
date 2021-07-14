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
const ll INF = 1e15;
const int INFN = 1000;
const int MOD = 1e9 + 7;

const int MX = 3010;

struct Edge {
	int from, to, capacity, flow;
	ll cost;
	Edge* reverse;
};
Edge edges[4 * MX];
int ecnt = 0;
Edge* new_edge(){
	return &edges[ecnt++];
}

vector<Edge*> adj[MX];

void add_edge(int u, int v, int cp, ll co) {
	Edge* ef = new_edge();
	Edge* er = new_edge();
	*ef = { u, v, cp, 0, co, er };
	*er = { v, u, 0, 0, -co, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int total_flow;
ll total_cost;
int MCMF(int n, int source, int sink) {
	total_flow = 0;
	total_cost = 0;

	while (1) {
		vector<Edge*> prev(n, NULL);
		vector<ll> dist(n, INF);
		vector<int> inque(n, 0);
		queue<int> q;

		q.push(source); inque[source] = 1;
		dist[source] = 0;

		while (!q.empty()) {
			int now = q.front(); q.pop(); inque[now] = 0;
			for (Edge* e : adj[now]) {
				if (e->capacity - e->flow > 0 && dist[now] + e->cost < dist[e->to]) {
					dist[e->to] = dist[now] + e->cost;
					prev[e->to] = e;

					if (!inque[e->to]) {
						q.push(e->to); inque[e->to] = 1;
					}
				}
			}
		}

		if (prev[sink] == NULL) break;

		int amount = INFN;
		for (int p = sink; p != source; p = prev[p]->from)
			amount = min(amount, prev[p]->capacity - prev[p]->flow);

		for (int p = sink; p != source; p = prev[p]->from) {
			total_cost += amount * prev[p]->cost;
			prev[p]->flow += amount;
			prev[p]->reverse->flow -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}

vector< pair<int, ll> > tadj[MX];

void dfs(int now, int p){
	for (auto e : tadj[now]){
		if (e.first == p) continue;
		add_edge(now, e.first, 1, -e.second);
		dfs(e.first, now);
	}
}


int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		int s, t, mx;
		ll ans;

		scanf("%d %d", &n, &m);
		s = 0;
		t = m + n + 1;
		mx = m + n + 5;
		for (int i = 0; i < mx; i++){
			tadj[i].clear();
		}

		for (int i = 0; i < m - 1; i++){
			int u, v;
			ll w;
			scanf("%d %d %lld", &u, &v, &w);
			tadj[u].push_back({ v, w });
			tadj[v].push_back({ u, w });
		}

		ans = 0;
		for (int root = 1; root <= 2 * n; root += n){
			ecnt = 0;
			for (int i = 0; i < mx; i++){
				adj[i].clear();
			}
			dfs(root, -1);

			for (int i = 1; i <= m; i++){
				add_edge(s, i, INFN, 0);
			}
			for (int i = 2; i <= n; i++){
				add_edge(i, i + m, 1, 0);
				add_edge(n + i, i + m, 1, 0);
				add_edge(i + m, t, 1, 0);
			}
			MCMF(mx, s, t);
			ans = max(ans, -total_cost);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
