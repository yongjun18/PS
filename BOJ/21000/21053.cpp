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

int arr[1000100];

int main()
{
	int n;
	ll cnt1, casenum, ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	cnt1 = casenum = ans = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] == 1) cnt1++;
		if (arr[i] == 2) casenum = (casenum * 2 + cnt1) % MOD;
		if (arr[i] == 3) ans = (ans + casenum) % MOD;
	}
	printf("%lld\n", ans);

	return 0;
}
