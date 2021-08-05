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

ll arr[300100];
ll psum[300100];

multiset<ll> ms;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		ll m;
		ll ans;

		scanf("%d %lld", &n, &m);
		ms.clear();

		psum[0] = 0;
		for (int i = 1; i <= n; i++){
			scanf("%lld", &arr[i]);
			psum[i] = psum[i - 1] + arr[i];
		}

		ans = 0;
		for (int i = n; i >= 1; i--){
			ms.insert(psum[i]);
			auto it = ms.upper_bound(m + psum[i - 1]);
			
			if (it == ms.begin()) continue;
			ans = max(ans, *prev(it) - psum[i - 1]);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
