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

ll arr[400100];

int main()
{
	int n;
	ll c;
	ll maxv1, maxv2;

	scanf("%d %lld", &n, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}

	maxv1 = maxv2 = -INF;

	for (int i = 1; i <= n; i++) {
		ll ans = 0;
		if (i > 1) {
			ans = max(ans, maxv1 + arr[i] - c * i);
			ans = max(ans, maxv2 - c * i - arr[i]);
		}
		printf("%lld ", ans);

		maxv1 = max(maxv1, c * i - arr[i]);
		maxv2 = max(maxv2, arr[i] + c * i);
	}
	printf("\n");

	return 0;
}
