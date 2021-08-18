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

int to[200100];

int solve(ll x, int i, int r){
	return x * x + (ll)i * i < (ll)r * r;
}

ll psearch(ll x, ll y, int i, int r) {
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (solve(mid, i, r)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int r;
		ll ans, tmp;

		scanf("%d", &r);
		for (int i = r - 1; i >= 1; i--){
			to[i] = psearch(0, r, i, r);
		}

		ans = 1;
		tmp = (to[r - 1] + 1) * (r - 1);
		for (int i = r - 2; i >= 1; i--){
			tmp += (ll)(to[i] - to[i + 1]) * i;
		}
		ans += tmp * 4;

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
