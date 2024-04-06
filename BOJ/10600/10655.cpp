#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int x[100100];
int y[100100];
int dp[100100][2];

int dist(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}

	dp[0][0] = 0;
	dp[0][1] = INF;
	for (int i = 1; i < n; i++) {
		dp[i][0] = dp[i - 1][0] + dist(x[i - 1], y[i - 1], x[i], y[i]);
		dp[i][1] = dp[i - 1][1] + dist(x[i - 1], y[i - 1], x[i], y[i]);
		if (i - 2 >= 0) {
			dp[i][1] = min(dp[i][1], dp[i - 2][0] + dist(x[i - 2], y[i - 2], x[i], y[i]));
		}
	}

	printf("%d\n", dp[n - 1][1]);
	return 0;
}
