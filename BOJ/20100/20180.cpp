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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

ll arr[1000100];
ll le[1000100];
ll ri[1000100];
ll ans;

void compute(int l, int r, int optl, int optr){
	if (l > r) return;

	int mid = (l + r) / 2;
	int opt = -1;
	ll maxv = 0;

	for (int i = max(mid, optl); i <= optr; i++){
		ll nowv = (le[mid] + ri[i]) * (i - mid);
		if (maxv <= nowv){
			maxv = nowv;
			opt = i;
		}
	}
	ans = max(ans, maxv);

	compute(l, mid - 1, optl, opt);
	compute(mid + 1, r, opt, optr);
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}
	
	le[0] = arr[0];
	for (int i = 1; i < n; i++){
		le[i] = max(le[i - 1], arr[i]);
	}
	ri[n - 1] = arr[n - 1];
	for (int i = n - 2; i >= 0; i--){
		ri[i] = max(ri[i + 1], arr[i]);
	}

	ans = 0;
	compute(0, n - 1, 0, n - 1);
	printf("%lld\n", ans);
	return 0;
}
