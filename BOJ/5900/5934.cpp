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
int dp[50100];
int selected[50100];

void dfs(int now, int pv) {
	selected[now] = 1;
	for (int nxt : adj[now]) {
		if (nxt == pv) continue;
		dfs(nxt, now);
		dp[now] += dp[nxt];
		if (selected[nxt]) selected[now] = 0;
	}
	dp[now] += selected[now];
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	dfs(1, -1);
	printf("%d\n", dp[1]);
	return 0;
}	
