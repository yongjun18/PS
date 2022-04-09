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

vector<int> adj[50100];

int parent[50100][18];
int depth[50100];
ll res[50100];
ll diff[50100];

void add_edge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void dfs(int now) {
	for (int next : adj[now]) {
		if (depth[next] != -1) continue;

		depth[next] = depth[now] + 1;
		parent[next][0] = now;
		dfs(next);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));

	depth[0] = 0;
	dfs(0);

	for (int k = 0; k < 18 - 1; k++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][k] != -1)
				parent[i][k + 1] = parent[parent[i][k]][k];
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		if (ancu != -1 && depth[ancu] >= depth[v])
			u = ancu;
	}
	if (u == v) return u;

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		int ancv = parent[v][k];

		if (ancu == ancv) continue;
		u = ancu;
		v = ancv;
	}
	u = parent[u][0];
	return u;
}

void dfs2(int now, int pv) {
	for (int nxt : adj[now]) {
		if (nxt == pv)continue;
		dfs2(nxt, now);
		res[now] += res[nxt];
	}
	res[now] += diff[now];
}

int main()
{
	int n, k;
	ll ans;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add_edge(x, y);
	}
	add_edge(0, 1);
	build(n + 1);

	for (int i = 0; i < k; i++) {
		int u, v, lca;
		scanf("%d %d", &u, &v);
		lca = LCA(u, v);

		diff[u]++;
		diff[parent[lca][0]]--;
		diff[v]++;
		diff[lca]--;
	}

	dfs2(0, -1);
	ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, res[i]);
	}
	printf("%lld\n", ans);

	return 0;
}
