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

typedef pair<int, int> pii;

int n, m;
int vis[105][105];
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int valid(int x, int y) {
	return (0 <= x && x <= n && 0 <= y && y <= m);
}

int bfs(pii b1, pii b2) {
	vector<pii> v1, v2;
	int x = b1.first;
	int y = b1.second;

	vis[x][y] = 1;
	v1.push_back({ x, y });
	for (int t = 1; v1.size(); t++) {
		for (auto it : v1) {
			int x = it.first;
			int y = it.second;
			for (int d = 0; d < 4; d++) {
				int nx = x + dx[d];
				int ny = y + dy[d];
				if (b2 == make_pair(nx, ny)) return t;
				if (valid(nx, ny) && vis[nx][ny] == 0) {
					vis[nx][ny] = 1;
					v2.push_back({ nx, ny });
				}
			}
		}
		swap(v1, v2);
		v2.clear();
	}
	return INF;
}

int test(pii a1, pii a2, pii b1, pii b2, int mid) {
	int ret = 0;
	int x = a1.first;
	int y = a1.second;
	memset(vis, 0, sizeof(vis));

	vis[x][y] = 1;
	while (x + 1 <= mid) {
		x++;
		if (b1 == make_pair(x, y)) return INF;
		if (b2 == make_pair(x, y)) return INF;
		vis[x][y] = 1;
		ret++;
	}
	while (y + 1 <= a2.second) {
		y++;
		if (b1 == make_pair(x, y)) return INF;
		if (b2 == make_pair(x, y)) return INF;
		vis[x][y] = 1;
		ret++;
	}
	while (y - 1 >= a2.second) {
		y--;
		if (b1 == make_pair(x, y)) return INF;
		if (b2 == make_pair(x, y)) return INF;
		vis[x][y] = 1;
		ret++;
	}
	while (x + 1 <= a2.first) {
		x++;
		if (b1 == make_pair(x, y)) return INF;
		if (b2 == make_pair(x, y)) return INF;
		vis[x][y] = 1;
		ret++;
	}
	return ret + bfs(b1, b2);
}


int main()
{
	pii a1, a2, b1, b2;
	int ans;

	scanf("%d %d", &n, &m);
	scanf("%d %d", &a1.first, &a1.second);
	scanf("%d %d", &a2.first, &a2.second);
	scanf("%d %d", &b1.first, &b1.second);
	scanf("%d %d", &b2.first, &b2.second);

	if (a1 > a2) swap(a1, a2);
	if (b1 > b2) swap(b1, b2);

	ans = INF;
	for (int t = 0; t < 2; t++) {
		for (int i = a1.first; i <= a2.first; i++) {
			ans = min(ans, test(a1, a2, b1, b2, i));
		}
		for (int i = b1.first; i <= b2.first; i++) {
			ans = min(ans, test(b1, b2, a1, a2, i));
		}
		swap(a1.first, a1.second);
		swap(a2.first, a2.second);
		swap(b1.first, b1.second);
		swap(b2.first, b2.second);
		if (a1 > a2) swap(a1, a2);
		if (b1 > b2) swap(b1, b2);
	}

	if (a1.first == a2.first && a2.first == b1.first && b1.first == b2.first) {
		if (0 < a1.first && a1.first < n) {
			ans = min(ans, abs(a1.second - a2.second) + abs(b1.second - b2.second) + 4);
		}
	}
	if (a1.second == a2.second && a2.second == b1.second && b1.second == b2.second) {
		if (0 < a1.second && a1.second < m) {
			ans = min(ans, abs(a1.first - a2.first) + abs(b1.first - b2.first) + 4);
		}
	}
	if (ans >= INF) printf("IMPOSSIBLE\n");
	else printf("%d\n", ans);
	return 0;
}
