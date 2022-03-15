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

int arr[100100];
int dp[100100][31];
int ans[100100];

int main()
{
	int n, m, t;

	scanf("%d %d %d", &n, &m, &t);
	for (int i = 1; i <= n; i++) {
		arr[i] = i;
	}
	while (m--) {
		int l, r;
		scanf("%d %d", &l, &r);
		reverse(arr + l, arr + r + 1);
	}

	for (int i = 1; i <= n; i++) {
		dp[arr[i]][0] = i;
	}
	for (int k = 1; k <= 30; k++) {
		for (int i = 1; i <= n; i++) {
			dp[i][k] = dp[dp[i][k - 1]][k - 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		int dest = i;
		for (int k = 30; k >= 0; k--) {
			if (t & (1 << k)) {
				dest = dp[dest][k];
			}
		}
		ans[dest] = i;
	}

	for (int i = 1; i <= n; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
