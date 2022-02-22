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

double dpf[460][3010];
double dp1[460][3010];
double dp2[460][3010];
double dp[460][3010];

int main()
{
	int n, k;

	scanf("%d %d", &n, &k);

	dpf[1][0] = 1.0;
	for (int i = 1; i <= k; i++) dp[i][0] = 1.0;

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= n; j++) {
			dpf[i][j] = dp2[i - 1][j] + dp1[i - 1][j] / 2 + dpf[i][j - 1] / 3;
			dp1[i][j] = dpf[i][j - 1] * 2 / 3;
			dp2[i][j] = dp1[i - 1][j] / 2;
			dp[i][j] = dp[i - 1][j] + dp1[i - 1][j] / 2 + dp2[i - 1][j] + dpf[i][j - 1] / 3;
		}
	}

	printf("%.9f\n", dp[k][n]);
	return 0;
}
