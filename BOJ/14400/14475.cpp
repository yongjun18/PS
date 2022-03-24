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

vector< pair<int, int> > adj[10010];
int t[10010];

void add_edge(int u, int v, int w) {
	adj[u].push_back({ v, w });
	adj[v].push_back({ u, w });
}

int dist[10010][3][205];

void dijkstra(int n, int x, int start) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k <= x; k++) {
				dist[i][j][k] = INF;
			}
		}
	}
	dist[start][0][0] = 0;
	priority_queue< tuple<int, int, int, int> > pq;
	pq.push({ 0, start, 0, 0 });

	while (pq.size()) {
		int wsum, now, temp, tim;
		tie(wsum, now, temp, tim) = pq.top();
		wsum *= -1;
		pq.pop();

		if (dist[now][temp][tim] < wsum) continue;

		for (auto [nxt, w] : adj[now]) {
			int next, next_temp, next_tim, next_wsum;

			next = nxt;

			if (t[next] != 1) next_temp = t[next];
			else next_temp = temp;

			if (t[next] != 1 && temp != t[next] && tim + w < x) continue;

			if (t[next] == 1) next_tim = min(x, tim + w);
			else next_tim = 0;

			next_wsum = wsum + w;

			if (dist[next][next_temp][next_tim] > next_wsum) {
				dist[next][next_temp][next_tim] = next_wsum;
				pq.push({ -next_wsum, next, next_temp, next_tim });
			}
		}
	}
}



int main()
{
	int n, m, x;
	int ans;

	scanf("%d %d %d", &n, &m, &x);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t[i]);
	}
	while (m--) {
		int a, b, d;
		scanf("%d %d %d", &a, &b, &d);
		add_edge(a, b, d);
	}
	dijkstra(n + 5, x, 1);

	ans = INF;
	for (int i = 0; i <= x; i++) {
		ans = min(ans, dist[n][0][i]);
		ans = min(ans, dist[n][2][i]);
	}
	printf("%d\n", ans);
	return 0;
}
