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

ll arr1[200100];
ll arr2[200100];
ll dp[200100][2][2];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		ll ans;

		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%lld", &arr1[i]);
		}
		for (int i = 1; i <= n; i++){
			scanf("%lld", &arr2[i]);
		}
		sort(arr1 + 1, arr1 + 1 + n);
		sort(arr2 + 1, arr2 + 1 + n);

		for (int i = 1; i <= n; i++){
			for (int j = 0; j < 2; j++){
				for (int k = 0; k < 2; k++){
					dp[i][j][k] = INF;
				}
			}
		}
		for (int i = 1; i <= n - 1; i++){
			if (i == 1){
				dp[i][0][0] = min(dp[i][0][0], abs(arr1[1] - arr2[1]));
				dp[i][1][0] = min(dp[i][1][0], abs(arr1[2] - arr2[1]));
				dp[i][0][1] = min(dp[i][0][1], abs(arr1[1] - arr2[2]));
				dp[i][1][1] = min(dp[i][1][1], abs(arr1[2] - arr2[2]));
			}
			else{
				dp[i][0][0] = min(dp[i][0][0], dp[i - 1][0][0] + abs(arr1[i] - arr2[i]));

				dp[i][1][0] = min(dp[i][1][0], dp[i - 1][0][0] + abs(arr1[i + 1] - arr2[i]));
				dp[i][1][0] = min(dp[i][1][0], dp[i - 1][1][0] + abs(arr1[i + 1] - arr2[i]));

				dp[i][0][1] = min(dp[i][0][1], dp[i - 1][0][0] + abs(arr1[i] - arr2[i + 1]));
				dp[i][0][1] = min(dp[i][0][1], dp[i - 1][0][1] + abs(arr1[i] - arr2[i + 1]));

				dp[i][1][1] = min(dp[i][1][1], dp[i - 1][0][0] + abs(arr1[i + 1] - arr2[i + 1]));
				dp[i][1][1] = min(dp[i][1][1], dp[i - 1][1][0] + abs(arr1[i + 1] - arr2[i + 1]));
				dp[i][1][1] = min(dp[i][1][1], dp[i - 1][0][1] + abs(arr1[i + 1] - arr2[i + 1]));
				dp[i][1][1] = min(dp[i][1][1], dp[i - 1][1][1] + abs(arr1[i + 1] - arr2[i + 1]));
			}
		}

		ans = dp[n - 1][0][0];
		ans = min(ans, dp[n - 1][1][0]);
		ans = min(ans, dp[n - 1][0][1]);
		ans = min(ans, dp[n - 1][1][1]);

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
