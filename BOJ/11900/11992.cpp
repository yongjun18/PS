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

ll arr[2010];
ll wsum[2010][2010];
ll dp[10][1010];

void dnc(int cnt, int lo, int hi, int pvlo, int pvhi, int x) {
	if (lo > hi) return;
	int opt = -1;
	ll optv = INF;
	int mid = (lo + hi) / 2;
	for (int i = pvlo; i <= min(mid - 1, pvhi); i++) {
		ll val = dp[cnt - 1][i - x] + wsum[i + 1][mid];
		if (optv > val) {
			optv = val;
			opt = i;
		}
	}
	dp[cnt][mid - x] = optv;
	dnc(cnt, lo, mid - 1, pvlo, opt, x);
	dnc(cnt, mid + 1, hi, opt, pvhi, x);
}

ll solve(int x, int y, int k) {
	for (int i = x; i <= y; i++) {
		dp[1][i - x] = wsum[x][i];
	}
	for (int cnt = 2; cnt <= k; cnt++) {
		dnc(cnt, x, y, x, y, x);
	}
	return dp[k][y - x];
}

int main()
{
	int n, k;
	ll ans;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
		arr[i + n] = arr[i];
	}
	for (int i = 0; i < 2 * n; i++) {
		wsum[i][i] = 0;
		for (int j = i + 1; j < 2 * n; j++) {
			wsum[i][j] = wsum[i][j - 1] + arr[j] * (j - i);
		}
	}

	ans = INF;
	for (int i = 0; i < n; i++) {
		ans = min(ans, solve(i, i + n - 1, k));
	}
	printf("%lld\n", ans);
	return 0;
}
