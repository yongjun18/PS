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
const int MOD = 1e9 + 7;

int n, m;
ll arr[310][310];
ll dist[310][310];

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

struct QNode {
	int x, y;
	ll wsum;
	bool operator < (const QNode& rhs) const {
		return wsum > rhs.wsum;
	}
};

int valid(int x, int y) {
	return 0 <= x && x <= n + 1 && 0 <= y && y <= m + 1;
}

ll dijkstra() {
	priority_queue<QNode> pq;

	for (int i = 0; i < n + 5; i++) {
		for (int j = 0; j < m + 5; j++) {
			dist[i][j] = INF;
		}
	}
	dist[n + 1][0] = 0;
	pq.push({ n + 1, 0, 0 });

	while (pq.size()) {
		int x = pq.top().x;
		int y = pq.top().y;
		ll wsum = pq.top().wsum;
		pq.pop();

		if (dist[x][y] < wsum) continue;

		for (int d = 0; d < 8; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (valid(nx, ny) == 0) continue;
			ll ndist = wsum + arr[nx][ny];
			if (dist[nx][ny] > ndist) {
				dist[nx][ny] = ndist;
				pq.push({ nx, ny, ndist });
			}
		}
	}
	return dist[0][m + 1];
}

int main()
{
	ll res;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%lld", &arr[i][j]);
			if (arr[i][j] == -1) arr[i][j] = INF;
			if (arr[i][j] == -2) arr[i][j] = 0;
		}
	}
	arr[0][0] = arr[0][1] = arr[1][0] = INF;
	arr[n][m + 1] = arr[n + 1][m] = arr[n + 1][m + 1] = INF;

	res = dijkstra();
	if (res >= INF) printf("-1\n");
	else printf("%lld\n", res);
	return 0;
}
