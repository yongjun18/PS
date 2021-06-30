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
const ll INF = 1e12;
const int MOD = 1e9 + 7;

struct Edge{
	int to;
	ll w;
};
struct Node{
	int now;
	ll wsum;
	bool operator < (const Node& rhs) const{
		return wsum > rhs.wsum;
	}
};

vector<Edge> adj[1010];
vector<ll> dist;
vector<int> pv[1010];
int can[1010];
priority_queue<Node> pq;

void dijkstra(int start, int n){
	for (int i = 1; i <= n; i++){
		pv[i].clear();
	}
	while (pq.size()) pq.pop();
	dist = vector<ll>(n + 1, INF);

	dist[start] = 0;
	pq.push({ start, 0 });
	while (pq.size()){
		int now = pq.top().now;
		ll wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] != wsum) continue;

		for (Edge e : adj[now]){
			if (dist[e.to] > dist[now] + e.w){
				dist[e.to] = dist[now] + e.w;
				pq.push({ e.to, dist[e.to] });
				pv[e.to].clear();
			}
			if (dist[e.to] == dist[now] + e.w){
				if (now != start){
					pv[e.to].push_back(now);
				}
			}
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
		vector<int> ans;
		scanf("%d %d", &n, &m);
		
		for (int i = 1; i <= n; i++){
			adj[i].clear();
			can[i] = 0;
		}
		while (m--){
			int u, v;
			ll w;
			scanf("%d %d %lld", &u, &v, &w);
			adj[u].push_back({ v, w });
			adj[v].push_back({ u, w });
		}

		for (int i = 1; i <= n; i++){
			dijkstra(i, n);
			for (int i = 1; i <= n; i++){
				for (int it : pv[i]){
					can[it] = 1;
				}
			}
		}
		
		for (int i = 1; i <= n; i++){
			if (can[i] == 0){
				ans.push_back(i);
			}
		}

		printf("Case #%d\n", test);
		printf("%d", ans.size());
		for (int it : ans){
			printf(" %d", it);
		}
		printf("\n");
	}

	return 0;
}
