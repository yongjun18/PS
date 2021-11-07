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

ll dist[100100];
ll price[100100];
ll minv[100100];
ll dp[100100];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%lld", &dist[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%lld", &price[i]);
	}
	minv[0] = price[0];
	for (int i = 1; i < n; i++) {
		minv[i] = min(minv[i - 1], price[i]);
	}

	dp[0] = 0;
	for (int i = 1; i < n; i++) {
		dp[i] = dp[i - 1] + minv[i - 1] * dist[i];
	}
	printf("%lld\n", dp[n - 1]);
	return 0;
}
