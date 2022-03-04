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

int cut[10100];
int dp[2][10100];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d", &cut[i]);
	}

	dp[1][1] = 0;
	for (int i = 2; i <= n; i++) {
		int now = (i & 1);
		int pv = (now ^ 1);

		for (int j = 1; j <= i - 1; j++) {
			dp[now][j + 1] = dp[pv][j];
		}

		dp[now][1] = cut[i - 1];
		for (int j = 1; j <= i - 1; j++) {
			dp[now][j + 1] = min(dp[now][j + 1], dp[pv][j] + cut[i - 1]);
			dp[now][(i - 1) - j + 1] = min(dp[now][(i - 1) - j + 1], dp[pv][j] + cut[i - 1]);
		}
	}
	printf("%d\n", dp[n & 1][n / 2]);
	return 0;
}
