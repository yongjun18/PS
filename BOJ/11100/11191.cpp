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

	for (int j = 60; j >= 0; j--) {
		for (int i = 1; i <= n; i++) {
			if (sel[i]) continue;

			if (arr[i] & (1LL << j)) {
				basis[j] = i;
				sel[i] = 1;
				for (int k = 1; k <= n; k++) {
					if (k == i) continue;
					if (arr[k] & (1LL << j)) {
						arr[k] ^= arr[i];
					}
				}
				break;
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
