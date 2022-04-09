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

struct Edge { int nxt, w; };
vector<Edge> adj[100100];
int vis[100100];
int down[100100][2];
int up[100100];

vector<int> comp;
int diamax;

void dfs1(int now, int pv, vector<int>& v) {
	vector<int> tmp;
	tmp.push_back(0);
	tmp.push_back(0);

	vis[now] = 1;
	v.push_back(now);

	for (auto[nxt, w] : adj[now]) {
		if (nxt == pv) continue;
		dfs1(nxt, now, v);
		tmp.push_back(down[nxt][0] + w);
	}
	sort(tmp.begin(), tmp.end());
	for (int i = 0; i < 2; i++) {
		down[now][i] = *(tmp.rbegin() + i);
	}
}

void dfs2(int now, int pv) {
	for (auto[nxt, w] : adj[now]) {
		if (nxt == pv) continue;

		up[nxt] = up[now] + w;

		int maxi = 0;
		if (down[now][maxi] == down[nxt][0] + w) maxi++;

		up[nxt] = max(up[nxt], down[now][maxi] + w);
		dfs2(nxt, now);
	}
}

int main()
{
	int n, m, l;
	int ans;

	scanf("%d %d %d", &n, &m, &l);
	for (int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });
	}

	for (int i = 0; i < n; i++) {
		if (vis[i]) continue;
		vector<int> v;
		int minv = INF;

		dfs1(i, -1, v);
		dfs2(i, -1);

		for (int it : v) {
			minv = min(minv, max(down[it][0], up[it]));
			diamax = max(diamax, down[it][0] + down[it][1]);
			diamax = max(diamax, down[it][0] + up[it]);
		}
		comp.push_back(minv);
	}

	ans = diamax;

	sort(comp.rbegin(), comp.rend());
	if (comp.size() > 1) {
		ans = max(ans, comp[0] + comp[1] + l);
	}
	if (comp.size() > 2) {
		ans = max(ans, comp[1] + comp[2] + 2 * l);
	}
	printf("%d\n", ans);
	return 0;
}
