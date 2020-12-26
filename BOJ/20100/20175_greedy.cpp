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

ll solve(){
	ll minv, maxv;
	minv = maxv = arr[0];

	for (int i = 1; i < n; i++){
		minv = min(minv, arr[i] - i * d);
		maxv = max(maxv, arr[i] - i * d);
	}
	return maxv - minv;
}

int main()
{
	ll res1, res2, ans;

	scanf("%d %lld", &n, &d);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}

	res1 = solve();
	reverse(arr, arr + n);
	res2 = solve();
	ans = min(res1, res2);
	
	printf("%lld", ans / 2);
	if (ans & 1) printf(".5\n");
	else printf(".0\n");

	return 0;
}
