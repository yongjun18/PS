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

int n;
ll d;
ll arr[1000100];

int solve(ll dis){
	ll x = arr[0] - dis;
	ll y = arr[0] + dis;

	for (int i = 1; i < n; i++){
		ll nx = arr[i] - dis;
		ll ny = arr[i] + dis;
		x = max(x + d, nx);
		y = min(y + d, ny);
		
		if (x > y) {
			return 0;
		}
	}
	return 1;
}
ll parametric_search(ll x, ll y){
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
	ll res1, res2, ans;

	scanf("%d %lld", &n, &d);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
		arr[i] *= 2;
	}
	d *= 2;

	res1 = parametric_search(0, 1e17);
	reverse(arr, arr + n);
	res2 = parametric_search(0, 1e17);
	ans = min(res1, res2);

	printf("%lld", ans / 2);
	if (ans & 1) printf(".5\n");
	else printf(".0\n");

	return 0;
}
