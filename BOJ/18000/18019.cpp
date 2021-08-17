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
const ll INF = 6e18;
const int MOD = 1e9 + 7;

ll a[3], b[3];

ll case_r(){
	ll w = a[0] + a[1] + a[2];
	ll h = max({ b[0], b[1], b[2] });
	return w * h;
}
ll case_t(){
	ll w = max(a[0], a[1] + a[2]);
	ll h = b[0] + max(b[1], b[2]);
	return w * h;
}


int main()
{
	int t;

	scanf("%d", &t);

	while (t--){
		ll ans;
		scanf("%lld %lld %lld %lld %lld %lld", &a[0], &b[0], &a[1], &b[1], &a[2], &b[2]);

		ans = INF;

		for (int mask = 0; mask < 8; mask++){
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
			ans = min(ans, case_r());
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
		}

		for (int mask = 0; mask < 8; mask++){
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
			ans = min(ans, case_t());
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
		}

		swap(a[0], a[1]);
		swap(b[0], b[1]);
		for (int mask = 0; mask < 8; mask++){
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
			ans = min(ans, case_t());
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
		}

		swap(a[0], a[2]);
		swap(b[0], b[2]);
		for (int mask = 0; mask < 8; mask++){
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
			ans = min(ans, case_t());
			for (int i = 0; i < 3; i++){
				if (mask & (1 << i)) swap(a[i], b[i]);
			}
		}

		printf("%lld\n", ans);
	}

	return 0;
}
