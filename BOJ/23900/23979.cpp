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

const int MX = 100100;

struct Edge {
	int nxt;
	ll c;
};

vector<Edge> adj[MX];

int pcnt = 1;
int pos[MX];
int dp[MX];

int pre_order(int now, int p) {
	dp[now] = pos[now] = pcnt++;

	for (Edge e : adj[now]) {
		if (e.nxt == p) continue;
		dp[now] = max(dp[now], pre_order(e.nxt, now));
	}
	return dp[now];
}

int in_subtree(int x, int y) {
	return pos[y] <= pos[x] && pos[x] <= dp[y];
}

int depth[MX];
int w[MX];

int parent[MX][18];
ll sum[MX][18];
int maxe[MX][18];

void dfs(int now) {
	for (Edge e : adj[now]) {
		if (depth[e.nxt] != -1) continue;

		depth[e.nxt] = depth[now] + 1;
		parent[e.nxt][0] = now;
		sum[e.nxt][0] = e.c;
		maxe[e.nxt][0] = e.nxt;
		w[e.nxt] = e.c;
		dfs(e.nxt);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));

	depth[1] = 0;
	dfs(1);
	for (int k = 0; k < 18 - 1; k++) {
		for (int i = 1; i <= n; i++) {
			if (parent[i][k] != -1) {
				parent[i][k + 1] = parent[parent[i][k]][k];
				sum[i][k + 1] = sum[i][k] + sum[parent[i][k]][k];

				int e1 = maxe[i][k];
				int e2 = maxe[parent[i][k]][k];
				if (w[e1] < w[e2]) maxe[i][k + 1] = e2;
				else maxe[i][k + 1] = e1;
			}
		}
	}
}

pair<ll, int> LCA(int u, int v) {
	if (u == v) return make_pair(0, -1);
	if (depth[u] < depth[v]) swap(u, v);

	ll uv_sum = 0;
	int uv_maxe = 0;

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		if (ancu != -1 && depth[ancu] >= depth[v]) {
			uv_sum += sum[u][k];
			if (w[uv_maxe] < w[maxe[u][k]]) {
				uv_maxe = maxe[u][k];
			}
			u = ancu;
		}
	}
	if (u == v) return make_pair(uv_sum, uv_maxe);

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		int ancv = parent[v][k];

		if (ancu == ancv) continue;

		uv_sum += sum[u][k] + sum[v][k];
		if (w[uv_maxe] < w[maxe[u][k]]) {
			uv_maxe = maxe[u][k];
		}
		if (w[uv_maxe] < w[maxe[v][k]]) {
			uv_maxe = maxe[v][k];
		}

		u = ancu;
		v = ancv;
	}

	uv_sum += sum[u][0];
	uv_sum += sum[v][0];
	if (w[uv_maxe] < w[maxe[u][0]]) {
		uv_maxe = maxe[u][0];
	}
	if (w[uv_maxe] < w[maxe[v][0]]) {
		uv_maxe = maxe[v][0];
	}
	u = parent[u][0];
	return make_pair(uv_sum, uv_maxe);
}

int main()
{
	int n, q;

	scanf("%d %d", &n, &q);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		ll c;
		scanf("%d %d %lld", &u, &v, &c);
		adj[u].push_back({ v, c });
		adj[v].push_back({ u, c });
	}

	pre_order(1, -1);
	build(n);

	while (q--) {
		int u, v, w, a, b;
		scanf("%d %d %d %d %d", &u, &v, &w, &a, &b);

		int sub = LCA(u, v).second;
		if (in_subtree(a, sub) == in_subtree(b, sub)) {
			printf("%lld\n", LCA(a, b).first);
		}
		else {
			if (in_subtree(a, sub) != in_subtree(u, sub)) {
				swap(u, v);
			}
			printf("%lld\n", LCA(a, u).first + LCA(b, v).first + w);
		}
	}

	return 0;
}
