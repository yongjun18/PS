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

const int MX = 20100;

int arr[10100];
int cnt[MX * 2];

int main()
{
	int n;
	ll ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	ans = 0;
	for (int i = 0; i < n; i++) {
		ans += cnt[-arr[i] + MX];
		for (int j = 0; j < i; j++) {
			cnt[arr[i] + arr[j] + MX]++;
		}
	}

	printf("%lld\n", ans);
	return 0;
}
