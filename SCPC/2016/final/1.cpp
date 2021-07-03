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

ll th[200100];
ll lh[200100];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		int idx;
		ll minv, ans;

		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			scanf("%lld", &th[i]);
		}
		for (int i = 0; i < n; i++){
			scanf("%lld", &lh[i]);
		}

		minv = INF;
		idx = -1;
		for (int i = 0; i < n; i++){
			if (minv > lh[i] - i){
				minv = lh[i] - i;
				idx = i;
			}
		}

		ans = 0;
		for (int i = 0; i < n; i++){
			ans += max(0LL, (th[i] + idx) - lh[idx]);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
