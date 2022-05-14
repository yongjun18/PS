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
const ll INF = 1e16;
const int MOD = 1e9 + 7;

int n, d;
ll t[100100];
ll v[100100];

ll solve(int flo, int fhi, int tlo, int thi) {
	if (flo > fhi) return -INF;
	
	int fmid = (flo + fhi) / 2;
	int opt = -1;
	ll optv = -INF;
	ll ret;

	for (int i = max(fmid, tlo); i <= min(fmid + d, thi); i++) {
		ll val = (i - fmid) * t[i] + v[fmid];
		if (optv < val) {
			optv = val;
			opt = i;
		}
	}
	ret = optv;
	ret = max(ret, solve(flo, fmid - 1, tlo, opt));
	ret = max(ret, solve(fmid + 1, fhi, opt, thi));
	return ret;
}

int main()
{
	scanf("%d %d", &n, &d);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &t[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld", &v[i]);
	}
	printf("%lld\n", solve(0, n-1, 0, n-1));
	return 0;
}
