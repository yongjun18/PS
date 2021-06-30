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

const ll MAXD = 3e9;

int n;
ll r, l;

ll arr[100100];

int solve(ll x){
	ll cover = 0;
	ll dx;

	for (int i = 0; i < n; i++){
		if (arr[i] <= cover + r){
			dx = cover + r - arr[i];
			dx = min(dx, x);
			cover = max(cover, arr[i] + dx + r);
		}
		else{
			if (arr[i] - (cover + r) <= x){
				cover = cover + 2 * r;
			}
		}
	}
	if (cover >= l) return 1;
	else return 0;
}
ll bsearch(ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		ll res;

		scanf("%d %lld %lld", &n, &r, &l);
		for (int i = 0; i < n; i++){
			scanf("%lld", &arr[i]);
		}
		res = bsearch(0, MAXD);

		printf("Case #%d\n", test);	
		if (res > MAXD){
			printf("-1\n");
		}
		else{
			printf("%lld\n", res);
		}
	}

	return 0;
}
