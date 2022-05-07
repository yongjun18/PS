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

ll arr[100100];
int sel[100100];
int basis[65];

int main()
{
	int n;
	ll ans;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}

	for (int bit = 60; bit >= 0; bit--) {
		int b1 = 1;
		int b0 = 1;
		while (b1 <= n && (sel[b1] || ((1LL << bit) & arr[b1]) == 0)) 
			b1++;
		while (b0 <= n && (sel[b0] || ((1LL << bit) & arr[b0]) != 0))
			b0++;
		if (b1 <= n && b0 <= n) {
			arr[b1] ^= arr[b0];
			sel[b1] = 1;
			basis[bit] = b1;
			for (int i = 1; i <= n; i++) {
				if (i == b1) continue;
				if ((1LL << bit) & arr[i]) {
					arr[i] ^= arr[b1];
				}
			}
		}
	}

	ans = 0;
	for (int i = 60; i >= 0; i--) {
		ans ^= arr[basis[i]];
	}
	printf("%lld\n", ans);
	return 0;
}
