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

vector<int> adj[510];
vector< pair<int, int> > eds;
int vis[2010];
int ans[2010];

int dfs(int now, int dest){
	if (now == dest) return 1;

	vis[now] = 1;
	for (int nxt : adj[now]){
		if (vis[nxt]) continue;
		if (dfs(nxt, dest)) return 1;
	}
	return 0;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m, k;

		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
		}
		eds.clear();

		for (int i = 0; i < m; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
		}
		for (int i = 0; i < k; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			eds.push_back({ u, v });
		}

		for (int i = 0; i < k; i++){
			int u = eds[i].first;
			int v = eds[i].second;
			for (int i = 0; i < n + 5; i++) vis[i] = 0;

			int res = dfs(v, u);
			ans[i] = res;

			if (res == 0) adj[u].push_back(v);
			else adj[v].push_back(u);
		}

		printf("Case #%d\n", test);
		for (int i = 0; i < k; i++){
			printf("%d", ans[i]);
		}
		printf("\n");
	}

	return 0;
}
