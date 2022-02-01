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
const ll MOD = (1 << 31) - 1;

int n;
char arr[1010][1010];
ll dp[1010][1010];
int vis[1010][1010];

int valid(int x, int y) {
	return (1 <= x && x <= n && 1 <= y && y <= n);
}

int dfs(int x, int y) {
	if (valid(x, y) == 0) return 0;
	if (vis[x][y]) return 0;
	if (arr[x][y] == '#') return 0;
	if (x == n && y == n) return 1;
	vis[x][y] = 1;

	if (dfs(x - 1, y)) return 1;
	if (dfs(x + 1, y)) return 1;
	if (dfs(x, y - 1)) return 1;
	if (dfs(x, y + 1)) return 1;
	return 0;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", arr[i] + 1);
	}

	dp[1][1] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 1 && j == 1) continue;
			if (arr[i][j] == '#') continue;
			dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
		}
	}

	if (dp[n][n] > 0) {
		printf("%lld\n", dp[n][n]);
	}
	else if (dfs(1, 1)) {
		printf("THE GAME IS A LIE\n");
	}
	else {
		printf("INCONCEIVABLE\n");
	}
	return 0;
}
