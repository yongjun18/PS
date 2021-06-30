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

ll arr[1000100];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, now, ans;
		ll k;

		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%lld", &arr[i]);
		}
		scanf("%lld", &k);

		now = 0;
		ans = 0;
		while (1){
			int nxt = upper_bound(arr, arr + n + 1, arr[now] + k) - arr - 1;
			if (nxt == now) break;
			now = nxt;
			ans++;
		}
		
		printf("Case #%d\n", test);
		if (now != n){
			printf("-1\n");
		}
		else{
			printf("%d\n", ans);
		}
	}

	return 0;
}
