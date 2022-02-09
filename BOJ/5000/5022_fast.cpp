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
int go_up(pii a2, pii b1, pii b2, pii& now) {
	pii tmp = now;
	tmp.first--;
	if (a2.first >= now.first) return 0;
	if (tmp == b1 || tmp == b2) return 0;

	now = tmp;
	vis[now.first][now.second] = 1;
	return 1;
}
int go_dn(pii a2, pii b1, pii b2, pii& now) {
	pii tmp = now;
	tmp.first++;
	if (a2.first <= now.first) return 0;
	if (tmp == b1 || tmp == b2) return 0;

	now = tmp;
	vis[now.first][now.second] = 1;
	return 1;
}
int go_le(pii a2, pii b1, pii b2, pii& now) {
	pii tmp = now;
	tmp.second--;
	if (a2.second >= now.second) return 0;
	if (tmp == b1 || tmp == b2) return 0;

	now = tmp;
	vis[now.first][now.second] = 1;
	return 1;
}
int go_ri(pii a2, pii b1, pii b2, pii& now) {
	pii tmp = now;
	tmp.second++;
	if (a2.second <= now.second) return 0;
	if (tmp == b1 || tmp == b2) return 0;

	now = tmp;
	vis[now.first][now.second] = 1;
	return 1;
}

int bfs(pii b1, pii b2) {
	int ret = 0;
	vector<pii> v1, v2;

	vis[b1.first][b1.second] = 1;
	v1.push_back(b1);

	for (int t = 1; v1.size(); t++) {
		for (auto it : v1) {
			for (int d = 0; d < 4; d++) {
				int nx = it.first + dx[d];
				int ny = it.second + dy[d];
				if (make_pair(nx, ny) == b2) return t;
				if (valid(nx, ny) == 0) continue;
				if (vis[nx][ny] == 1) continue;
				vis[nx][ny] = 1;
				v2.push_back({ nx, ny });
			}
		}
		swap(v1, v2);
		v2.clear();
	}
	return INF;
}

int test(pii a1, pii a2, pii b1, pii b2) {
	int ret = 0;
	pii now = a1;

	memset(vis, 0, sizeof(vis));
	vis[now.first][now.second] = 1;

	while (now != a2) {
		if (!go_up(a2, b1, b2, now) && !go_dn(a2, b1, b2, now) &&
			!go_le(a2, b1, b2, now) && !go_ri(a2, b1, b2, now)) {
			return INF;
		}
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

	ans = INF;
	for (int t = 0; t < 2; t++) {
		ans = min(ans, test(a1, a2, b1, b2));
		ans = min(ans, test(a2, a1, b1, b2));
		ans = min(ans, test(b1, b2, a1, a2));
		ans = min(ans, test(b2, b1, a1, a2));
		swap(a1.first, a1.second);
		swap(a2.first, a2.second);
		swap(b1.first, b1.second);
		swap(b2.first, b2.second);
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
