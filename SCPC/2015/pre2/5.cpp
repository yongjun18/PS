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

struct Edge{ int next, w; };
struct QNode{
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[510];
int need[510];
vector<int> pv[510];

void add_edge(int u, int v, int w){
	adj[u].push_back({ v, w });
	adj[v].push_back({ u, w });
}

vector<int> dist;

void dijkstra(int n, int start){
	dist = vector<int>(n + 1, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({ start, 0 });

	while (pq.size()){
		int now = pq.top().now;
		int wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]){
			int next = e.next;
			int next_dist = wsum + e.w;
			if (dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({ next, next_dist });
				pv[next].clear();
			}
			if (dist[next] == next_dist){
				pv[next].push_back(now);
			}
		}
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		vector<int> ans;

		scanf("%d %d", &n, &m);
		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
			need[i] = 0;
		}
		
		while (m--){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u, v, w);
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				pv[j].clear();
			}
			dijkstra(n, i);
			for (int j = 1; j <= n; j++){
				if (pv[j].size() == 1 && pv[j][0] != i){
					need[pv[j][0]] = 1;
				}
			}
		}

		for (int i = 1; i <= n; i++){
			if (need[i] == 1){
				ans.push_back(i);
			}
		}

		printf("Case #%d\n", test);
		printf("%d", ans.size());
		for (int it : ans) printf(" %d", it);
		printf("\n");
	}

	return 0;
}
