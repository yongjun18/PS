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

int p[10100];
int q[10100];
int dp[10100];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%d", &p[i]);
		}
		for (int i = 1; i <= n; i++){
			scanf("%d", &q[i]);
		}

		dp[0] = 0;
		dp[1] = max(p[1], q[1]);
		for (int i = 2; i <= n; i++){
			dp[i] = max(dp[i - 1] + p[i], dp[i - 2] + q[i]);
		}

		printf("Case #%d\n", test);
		printf("%d\n", dp[n]);
	}

	return 0;
}
