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

int n;
ll ans;
vector<int> adj[300100];
ll dp[300100];

void dfs(int now, int pv) {
	dp[now] = 1;
	
	for (int nxt : adj[now]) {
		if (nxt == pv)continue;
		dfs(nxt, now);
		dp[now] += dp[nxt];
		ans += dp[nxt] * (n - dp[nxt]);
		ans += dp[nxt] * (dp[nxt] - 1) / 2;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1, -1);
	printf("%lld\n", ans);

	return 0;
}
