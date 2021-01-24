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
using namespace std;
typedef long long ll;
const ll INF = 1e15;
const int MOD = 1e9 + 7;

ll c[8010];
ll psum[8010];
ll dp[810][8010];

void compute(int i, int l, int r, int optl, int optr){
	if (l > r) return;

	int mid = (l + r) / 2;
	int opt = min(mid, optr);
	ll best = dp[i-1][opt] + (psum[mid] - psum[opt]) * (mid - opt);

	for (int j = opt - 1; j >= optl; j--){
		ll now = dp[i - 1][j] + (psum[mid] - psum[j]) * (mid - j);
		if (best >= now){
			best = now;
			opt = j;
		}
	}
	dp[i][mid] = best;

	compute(i, l, mid - 1, optl, opt);
	compute(i, mid + 1, r, opt, optr);
}

int main()
{
	int l, g;

	scanf("%d %d", &l, &g);
	for (int i = 1; i <= l; i++){
		scanf("%lld", &c[i]);
	}
	for (int i = 1; i <= l; i++){
		psum[i] = psum[i - 1] + c[i];
	}

	dp[0][0] = 0;
	for (int i = 1; i <= l; i++){
		dp[0][i] = INF;
	}
	for (int i = 1; i <= g; i++){
		compute(i, 0, l, 0, l);
	}

	printf("%lld\n", dp[g][l]);
	return 0;
}
