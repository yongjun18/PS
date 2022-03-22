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

vector<Edge> adj[20100];

void add_edge(int u, int v, int w) {
	adj[u].push_back({ v, w });
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

int is_hub[20100];
vector<int> dist[20100];

int main()
{
	int n, m, k, q;
	int ans;
	ll sum;

	scanf("%d %d %d %d", &n, &m, &k, &q);
	while (m--) {
		int u, v, d;
		scanf("%d %d %d", &u, &v, &d);
		add_edge(u, v, d);
	}
	while (k--) {
		int x;
		scanf("%d", &x);
		is_hub[x] = 1;
	}

	for (int i = 1; i <= n; i++) {
		if (is_hub[i]) {
			dist[i] = dijkstra(n + 5, i);
		}
	}

	ans = sum = 0;
	while (q--) {
		int a, b;
		int minv = INF;
		
		scanf("%d %d", &a, &b);
		if (is_hub[a]) minv = dist[a][b];
		else {
			for (auto it : adj[a]) {
				minv = min(minv, it.w + dist[it.next][b]);
			}
		}
		if (minv < INF) {
			ans++;
			sum += minv;
		}
	}
	printf("%d\n", ans);
	printf("%lld\n", sum);
	return 0;
}
