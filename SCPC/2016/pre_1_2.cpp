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
const int MOD = 1e9 + 9;

int mine[50010];
ll dp[50010][110];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, k, l;
		ll ans;

		scanf("%d %d %d", &n, &k, &l);

		for (int i = 0; i < n + 5; i++){
			mine[i] = 0;
			for (int j = 0; j < k + 5; j++){
				dp[i][j] = 0;
			}
		}

		while (l--){
			int x;
			scanf("%d", &x);
			mine[x] = 1;
		}

		dp[0][0] = 1;
		for (int i = 0; i <= n; i++){
			ll sum = 0;
			for (int j = 0; j <= k; j++){
				sum += dp[i][j];
				sum %= MOD;
			}
			for (int jump = 1; jump <= k; jump++){
				if (i + jump > n) break;
				if (mine[i + jump]) continue;
				dp[i + jump][jump] += sum;
				dp[i + jump][jump] %= MOD;
			}
			for (int jump = 1; jump <= k; jump++){
				if (i + jump > n) break;
				if (mine[i + jump]) continue;
				dp[i + jump][jump] -= dp[i][jump];
				dp[i + jump][jump] += MOD;
				dp[i + jump][jump] %= MOD;
			}
		}

		ans = 0;
		for (int i = 0; i <= k; i++){
			ans += dp[n][i];
			ans %= MOD;
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
