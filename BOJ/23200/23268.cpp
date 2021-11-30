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

char arr[1010][1010];
char str[100100];
int vis[1010][1010];
int vis2[1010][1010];
int ans[1010][1010];

vector< pair<int, int> > can[100100];

int dx[] = { -1 , 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
char ds[] = "NSWE";

void bfs(int h, int w, int sx, int sy) {
	queue< pair<int, int> > que;
	
	memset(vis, -1, sizeof(vis));
	que.push({ sx, sy });
	vis[sx][sy] = 0;

	while (que.size()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int d = 0; d < 4; d++) {
			int nx = x + dx[d];
			int ny = y + dy[d];

			if (arr[nx][ny] == '.' && vis[nx][ny] == -1) {
				vis[nx][ny] = vis[x][y] + 1;
				que.push({ nx, ny });
			}
		}
	}
}

int main()
{
	int h, w;
	int sx, sy;
	int len;

	scanf("%d %d", &w, &h);
	for (int i = 0; i < h; i++) {
		scanf("%s", arr[i]);
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (arr[i][j] == 'S') {
				sx = i;
				sy = j;
			}
		}
	}
	scanf("%s", str);
	len = strlen(str);

	bfs(h, w, sx, sy);

	can[0].push_back({ sx, sy });

	for (int i = 0; i < len; i++) {
		for (auto it : can[i]) {
			int x = it.first;
			int y = it.second;

			for (int d = 0; d < 4; d++) {
				if (ds[d] == str[i]) continue;
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (vis[nx][ny] == i + 1 && vis2[nx][ny] == 0) {
					vis2[nx][ny] = 1;
					can[i + 1].push_back({ nx, ny });
				}
			}
		}
	}
	for (auto it : can[len]) {
		ans[it.first][it.second] = 1;
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (ans[i][j]) printf("!");
			else printf("%c", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
