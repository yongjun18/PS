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

const int MX = 200100;
pair<int, int> tree[MX * 2];

void update(int idx, pair<int, int> val) {
	for (tree[idx += MX] = val; idx > 1; idx >>= 1)
		tree[idx >> 1] = max(tree[idx], tree[idx ^ 1]);
}

pair<int, int> query(int l, int r) {
	pair<int, int> res = { 0, 0 };
	for (l += MX, r += MX; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = max(res, tree[l++]);
		if (r & 1) res = max(res, tree[--r]);
	}
	return res;
}

vector<int> used;
int cy(int y) {
	return lower_bound(used.begin(), used.end(), y) - used.begin();
}

int n, r, d;
// <x,y,idx> point
vector< tuple<int, int, int> > point;
vector<int> adj[100100];
int vis[100100];

void connectLR() {
	sort(point.begin(), point.end());

	for (auto[x, y, idx] : point) {
		auto upper = query(cy(y), cy(y + r + 1));
		auto lower = query(cy(y - r), cy(y));

		if (upper.second > 0 && x - upper.first <= d + r) {
			adj[idx].push_back(upper.second);
			adj[upper.second].push_back(idx);
		}
		if (lower.second > 0 && x - lower.first <= d + r) {
			adj[idx].push_back(lower.second);
			adj[lower.second].push_back(idx);
		}
		update(cy(y), make_pair(x, idx));
	}
}

void dfs(int now) {
	for (int nxt : adj[now]) {
		if (vis[nxt]) continue;
		vis[nxt] = 1;
		dfs(nxt);
	}
}

int main()
{
	int start = -1;
	int ans;

	scanf("%d %d", &n, &r);
	for (int i = 1; i <= n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		point.push_back({ x, y, i });
		if (x == 0 && y == 0) start = i;

		used.push_back(x);
		used.push_back(y);
	}
	scanf("%d", &d);
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	connectLR();
	for (auto &[x, y, idx] : point) swap(x, y);
	memset(tree, 0, sizeof(tree));
	connectLR();

	vis[start] = 1;
	dfs(start);

	ans = 0;
	for (auto[x, y, idx] : point) {
		if (vis[idx]) {
			ans = max(ans, x + y + 2 * r);
		}
	}
	printf("%d\n", ans);
	return 0;
}
