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

const int SLASH_0 = 0;
const int SLASH_1 = 1;
const int SLASH_2 = 2;
const int SLASH_3 = 3;

const int ARROW_0 = 4;
const int ARROW_2 = 5;

const int STICK_0 = 0;

const int TRI_0 = 1;
const int TRI_2 = 2;

const int DP = 0;

int n, k;
ll arr[3005][3005];
ll dp[3005][3005][6];

void init(int n, int type){
	for (int i = k - 1; i <= n - k; i++){
		dp[i][k - 1][type] = 0;
		dp[i][n - k][type] = 0;
	}
	for (int j = k - 1; j <= n - k; j++){
		dp[k - 1][j][type] = 0;
		dp[n - k][j][type] = 0;
	}
}

void get_slash(int i, int j){
	dp[i][j][SLASH_0] = dp[i - 1][j - 1][SLASH_0] + arr[i][j + k - 1] - arr[i - k + 1 - 1][j - 1];
	dp[i][j][SLASH_1] = dp[i - 1][j + 1][SLASH_1] + arr[i][j - k + 1] - arr[i - k + 1 - 1][j + 1];
	dp[i][j][SLASH_2] = dp[i - 1][j - 1][SLASH_2] + arr[i + k - 1][j] - arr[i - 1][j - k + 1 - 1];
	dp[i][j][SLASH_3] = dp[i - 1][j + 1][SLASH_3] + arr[i + k - 1][j] - arr[i - 1][j + k - 1 + 1];
}

void get_arrow(int i, int j){
	dp[i][j][ARROW_0] = dp[i][j][SLASH_0] + dp[i][j][SLASH_3] - arr[i][j + k - 1];
	dp[i][j][ARROW_2] = dp[i][j][SLASH_1] + dp[i][j][SLASH_2] - arr[i][j - k + 1];
}

void get_stick(int i, int j){
	dp[i][j][STICK_0] = dp[i - 1][j][STICK_0] + arr[i + k - 1][j] - arr[i - k + 1 - 1][j];
}

void get_tri(int i, int j){
	dp[i][j][TRI_0] = dp[i][j - 1][TRI_0] - dp[i][j - 1][STICK_0] + dp[i][j][ARROW_0];
	dp[i][j][TRI_2] = dp[i][j - 1][TRI_2] - dp[i][j - 1][ARROW_2] + dp[i][j][STICK_0];
}

void get_dp(int i, int j){
	dp[i][j][DP] = dp[i][j - 1][DP] - dp[i][j - 1][TRI_2] + dp[i][j][TRI_0];
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		ll ans;

		scanf("%d %d", &n, &k);
		for (int i = 0; i < k * 4 + n; i++){
			for (int j = 0; j < k * 4 + n; j++){
				arr[i][j] = 0;
			}
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%lld", &arr[i + k * 2][j + k * 2]);
			}
		}
		n = k * 4 + n;

		for (int i = 0; i < 6; i++){
			init(n, i);
		}

		for (int i = k; i <= n - k - 1; i++){
			for (int j = k; j <= n - k - 1; j++){
				get_slash(i, j);
			}
		}

		for (int i = k - 1; i <= n - k; i++){
			for (int j = k - 1; j <= n - k; j++){
				get_arrow(i, j);
			}
		}

		for (int i = k; i <= n - k - 1; i++){
			for (int j = k; j <= n - k - 1; j++){
				get_stick(i, j);
			}
		}

		for (int i = k; i <= n - k - 1; i++){
			for (int j = k; j <= n - k - 1; j++){
				get_tri(i, j);
			}
		}

		ans = 0;
		for (int i = k; i <= n - k - 1; i++){
			for (int j = k; j <= n - k - 1; j++){
				get_dp(i, j);
				ans = max(ans, dp[i][j][DP]);
			}
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
