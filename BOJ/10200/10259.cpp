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

struct Edge {
	int nxt, c;
};

vector<Edge> adj[MX];
int visit1[MX];
int visit2[MX];

int dfs(int x, int vis[]) {
	int ret = 0;
	
	for (Edge e : adj[x]) {
		if (vis[e.nxt] == -1) {
			if (e.c == 0) {
				if (vis[x] == 1) {
					vis[e.nxt] = 0;
					dfs(e.nxt, vis);
					ret = INF;
				}
				else {
					vis[e.nxt] = 0;
					ret += dfs(e.nxt, vis);
					ret = min(ret, INF);
				}
			}
			if (e.c == 1) {
				if (vis[x] == 1) {
					vis[e.nxt] = 0;
					ret += dfs(e.nxt, vis);
					ret = min(ret, INF);
				}
				else {
					vis[e.nxt] = 1;
					ret++;
					ret += dfs(e.nxt, vis);
					ret = min(ret, INF);
				}
			}
			if (e.c == 2) {
				if (vis[x] == 0) {
					vis[e.nxt] = 0;
					dfs(e.nxt, vis);
					ret = INF;
				}
				else {
					vis[e.nxt] = 1;
					ret++;
					ret += dfs(e.nxt, vis);
					ret = min(ret, INF);
				}
			}
		}
		else {
			if (vis[x] + vis[e.nxt] != e.c) {
				ret = INF;
			}
		}
	}
	return ret;
}

int main()
{
	int n, m;
	int ans;

	scanf("%d %d", &n, &m);
	while (m--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		adj[a].push_back({ b, c });
		adj[b].push_back({ a, c });
	}

	memset(visit1, -1, sizeof(visit1));
	memset(visit2, -1, sizeof(visit2));
	ans = 0;

	for (int i = 1; i <= n; i++) {
		if (visit1[i] == -1) {
			int res1, res2;
			
			visit1[i] = 1;
			res1 = dfs(i, visit1);
			res1++;

			visit2[i] = 0;
			res2 = dfs(i, visit2);
			
			ans += min(res1, res2);
			if (ans > INF) ans = INF;
		}
	}

	if (ans >= INF) printf("impossible\n");
	else printf("%d\n", ans);
	return 0;
}
