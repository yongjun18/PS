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
	int now;
	pair<int, int> wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[1010];

void add_edge(int u, int v, int w) {
	adj[u].push_back({ v, w });
}

int c[1010];
vector< pair<int, int> > dist;

void dijkstra(int n, int start) {
	dist = vector< pair<int, int> >(n, make_pair(INF, INF));;
	dist[start] = { 0, 0 };
	priority_queue<QNode> pq;
	pq.push({ start, {0, 0} });;

	while (pq.size()) {
		int now = pq.top().now;
		pair<int, int> wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]) {
			int next = e.next;

			pair<int, int> next_dist = wsum;
			if (c[now] != c[next]) next_dist.first++;
			next_dist.second += e.w;

			if (dist[next] > next_dist) {
				dist[next] = next_dist;
				pq.push({ next, next_dist });
			}
		}
	}
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &c[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int w;
			scanf("%d", &w);
			if (w > 0) {
				add_edge(i, j, w);
			}
		}
	}

	dijkstra(n, 0);

	printf("%d %d\n", dist[m].first, dist[m].second);
	return 0;
}
