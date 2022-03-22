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

struct Edge { int next, w; };
struct QNode {
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[10010];

void add_edge(int u, int v, int w) {
	adj[u].push_back({ v, w });
	adj[v].push_back({ u, w });
}

vector<int> dijkstra(int n, int start) {
	vector<int> dist = vector<int>(n, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({ start, 0 });

	while (pq.size()) {
		int now = pq.top().now;
		int wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]) {
			int next = e.next;
			int next_dist = wsum + e.w;
			if (dist[next] > next_dist) {
				dist[next] = next_dist;
				pq.push({ next, next_dist });
			}
		}
	}
	return dist;
}

int market[10010];
vector<int> mvec;
vector<int> dist[5];

int main()
{
	int n, m, k;
	int minv;
	vector<int> order;

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < k; i++) {
		int x;
		scanf("%d", &x);
		mvec.push_back(x);
		market[x] = 1;
	}
	while (m--) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);
		add_edge(a, b, l);
	}

	for (int i = 0; i < k; i++) {
		dist[i] = dijkstra(n + 5, mvec[i]);
		order.push_back(i);
	}

	minv = INF;
	while (1) {
		for (int start = 1; start <= n; start++) {
			if (market[start]) continue;
			int nowv = dist[order[0]][start] + dist[order.back()][start];

			for (int i = 0; i + 1 < order.size(); i++) {
				nowv += dist[order[i]][mvec[order[i + 1]]];
			}
			minv = min(minv, nowv);
		}
		if (next_permutation(order.begin(), order.end()) == 0) break;
	}
	printf("%d\n", minv);
	return 0;
}
