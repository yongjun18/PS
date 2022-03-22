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

int n, m, k;
int s, d;
int inc[30100];

struct Edge {
	int nxt, w;
};
vector<Edge> adj[1010];
vector<int> dist;
int res[1010];

void bfs(int start) {
	vector< pair<int, int> > v1, v2;
	dist = vector<int>(n + 5, INF);
	dist[start] = 0;
	v1.push_back({ 0, start });

	for (int t = 0; t < n; t++) {
		vector<int> inque(n + 5, 0);
		for (auto &it : v1) {
			it.first = dist[it.second];
		}
		for (auto it : v1) {
			int distv = it.first;
			int now = it.second;

			for (Edge e : adj[it.second]) {
				int nxt_dist = distv + e.w;
				if (dist[e.nxt] > nxt_dist) {
					dist[e.nxt] = nxt_dist;
					if (inque[e.nxt] == 0) {
						v2.push_back({ -1, e.nxt });
						inque[e.nxt] = 1;
					}
				}
			}
		}
		res[t + 1] = dist[d];
		swap(v1, v2);
		v2.clear();
	}
}

int main()
{
	int now;
	int total_inc;

	scanf("%d %d %d", &n, &m, &k);
	scanf("%d %d", &s, &d);

	while (m--) {
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		adj[a].push_back({ b, w });
		adj[b].push_back({ a, w });
	}
	for (int i = 0; i < k; i++) {
		scanf("%d", &inc[i]);
	}
	bfs(s);

	now = n;
	total_inc = 0;
	printf("%d\n", res[now]);

	for (int i = 0; i < k; i++) {
		int minv = INF;
		total_inc += inc[i];
		for (int i = 1; i <= n; i++) {
			minv = min(minv, res[i] + i * total_inc);
		}
		printf("%d\n", minv);
	}

	return 0;
}
