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
const int MOD = 1e4 + 7;

int comb[55][55];
	
int nCr(int n, int r){
	if (n < 0 || r < 0) return 0;
	if (r == 0) return comb[n][r] = 1;
	if (n == 0) return comb[n][r] = 0;
	int &ret = comb[n][r];
	if (ret != -1) return ret;
	return ret = nCr(n - 1, r - 1) + nCr(n - 1, r) % MOD;
}

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	memset(comb, -1, sizeof(comb));

	ans = 0;
	for (int i = 1; i <= n; i++){
		int now = nCr(13, i) * nCr(52 - 4 * i, n - 4 * i) % MOD;

		if (i & 1) ans += now;
		else ans -= now;
		ans = (ans % MOD + MOD) % MOD;
	}
	printf("%d\n", ans);
	return 0;
}
