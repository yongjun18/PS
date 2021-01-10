#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int r, c;
char arr[15][1050];
int blank[1050];
ll ans;

ll dp[1050][2];

void compute(int cnt){
	ll res;
	dp[0][0] = 1;
	dp[0][1] = (1 << blank[0]) - 1;
	
	for (int i = 0; i < c - 1; i++){
		ll nxt = (1 << blank[i + 1]) - 1;
		dp[i + 1][1] = dp[i + 1][0] = 0;

		dp[i + 1][1] += dp[i][0] * nxt % MOD;
		dp[i + 1][1] %= MOD;

		dp[i + 1][1] += dp[i][1] * nxt % MOD;
		dp[i + 1][1] %= MOD;

		dp[i + 1][0] += dp[i][1];
		dp[i + 1][0] %= MOD;
	}
	res = (dp[c - 1][0] + dp[c - 1][1]) % MOD;

	if ((r - cnt) & 1){
		ans -= res;
		ans = (ans % MOD + MOD) % MOD;
	}
	else{
		ans += res;
		ans %= MOD;
	}
}

void dfs(int x, int cnt){
	if (x == r){
		compute(cnt);
		return;
	}

	dfs(x + 1, cnt);
	
	for (int i = 0; i < c; i++){
		if (arr[x][i] == '.'){
			blank[i]++;
		}
	}
	dfs(x + 1, cnt + 1);
	for (int i = 0; i < c; i++){
		if (arr[x][i] == '.'){
			blank[i]--;
		}
	}
}

int main()
{
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++){
		scanf("%s", arr[i]);
	}

	ans = 0;
	dfs(0, 0);

	printf("%lld\n", ans);
	return 0;
}
