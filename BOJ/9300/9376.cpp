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

int h, w;
int xx1, yy1, xx2, yy2;
char arr[105][105];

int dist[105][105][2][2];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Node {
	int x, y, a, b, wsum;
	bool operator < (const Node& rhs) const {
		return wsum > rhs.wsum;
	}
};

int valid(int x, int y) {
	if (0 <= x && x < h && 0 <= y && y < w) {
		if (arr[x][y] != '*') {
			return 1;
		}
	}
	return 0;
}

void dijkstra() {
	priority_queue<Node> pq;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			for (int a = 0; a < 2; a++) {
				for (int b = 0; b < 2; b++) {
					dist[i][j][a][b] = INF;
				}
			}
		}
	}

	dist[xx1][yy1][1][0] = 0;
	dist[xx2][yy2][0][1] - 0;
	pq.push({ xx1, yy1, 1, 0, 0 });
	pq.push({ xx2, yy2, 0, 1, 0 });

	while (pq.size()) {
		int wsum = pq.top().wsum;
		int x = pq.top().x;
		int y = pq.top().y;
		int a = pq.top().a;
		int b = pq.top().b;
		pq.pop();

		if (dist[x][y][a][b] < wsum) continue;
		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (valid(nx, ny) == 0) continue;
			int ndist = wsum + (arr[nx][ny] == '#');
			if (dist[nx][ny][a][b] > ndist) {
				dist[nx][ny][a][b] = ndist;
				pq.push({ nx, ny, a, b, ndist });
			}
			if (a == 0 && b == 1) {
				ndist = wsum + dist[x][y][1][0] - (arr[x][y] == '#');
				if (dist[x][y][1][1] > ndist) {
					dist[x][y][1][1] = ndist;
					pq.push({ x, y, 1, 1, ndist });
				}
			}
			if (a == 1 && b == 0) {
				ndist = wsum + dist[x][y][0][1] - (arr[x][y] == '#');
				if (dist[x][y][1][1] > ndist) {
					dist[x][y][1][1] = ndist;
					pq.push({ x, y, 1, 1, ndist });
				}
			}
		}
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	while(t--) {
		int ans, minv1, minv2;

		scanf("%d %d", &h, &w);
		for (int i = 0; i < h; i++) {
			scanf("%s", arr[i]);
		}
		xx1 = xx2 = -1;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (arr[i][j] == '$') {
					if (xx1 == -1) { xx1 = i; yy1 = j; }
					else { xx2 = i; yy2 = j; }
				}
			}
		}
		dijkstra();

		ans = minv1 = minv2 = INF;
		for (int i = 0; i < h; i++) {
			minv1 = min(minv1, dist[i][0][1][0]);
			minv1 = min(minv1, dist[i][w - 1][1][0]);
			minv2 = min(minv2, dist[i][0][0][1]);
			minv2 = min(minv2, dist[i][w - 1][0][1]);
			ans = min(ans, dist[i][0][1][1]);
			ans = min(ans, dist[i][w - 1][1][1]);
		}
		for (int j = 0; j < w; j++) {
			minv1 = min(minv1, dist[0][j][1][0]);
			minv1 = min(minv1, dist[h - 1][j][1][0]);
			minv2 = min(minv2, dist[0][j][0][1]);
			minv2 = min(minv2, dist[h - 1][j][1][1]);
			ans = min(ans, dist[0][j][1][1]);
			ans = min(ans, dist[h - 1][j][1][1]);
		}
		ans = min(ans, minv1 + minv2);
		printf("%d\n", ans);
	}

	return 0;
}
