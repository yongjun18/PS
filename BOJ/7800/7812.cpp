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

struct Edge { int nxt; ll w; };

int n;
vector<Edge> adj[10100];
int siz[10100];
ll down[10100];
ll up[10100];

void dfs1(int now, int pv) {
	siz[now] = 1;
	for (auto[nxt, w] : adj[now]) {
		if (nxt == pv) continue;
		dfs1(nxt, now);
		siz[now] += siz[nxt];
		down[now] += down[nxt] + siz[nxt] * w;
	}
}

void dfs2(int now, int pv) {
	for (auto[nxt, w] : adj[now]) {
		if (nxt == pv) continue;
		up[nxt] = up[now] + down[now] - (down[nxt] + w * siz[nxt]) + (n - siz[nxt]) * w;
		dfs2(nxt, now);
	}
}

int main()
{
	ll ans;

	while (1) {
		scanf("%d", &n);
		if (n == 0) break;

		for (int i = 0; i < n + 5; i++) {
			adj[i].clear();
			down[i] = up[i] = siz[i] = 0;
		}
		for (int i = 0; i < n - 1; i++) {
			int a, b;
			ll w;
			scanf("%d %d %lld", &a, &b, &w);
			adj[a].push_back({ b, w });
			adj[b].push_back({ a, w });
		}
		dfs1(0, -1);
		dfs2(0, -1);

		ans = INF;
		for (int i = 0; i < n; i++) {
			ans = min(ans, down[i] + up[i]);
		}
		printf("%lld\n", ans);
	}

	return 0;
}
