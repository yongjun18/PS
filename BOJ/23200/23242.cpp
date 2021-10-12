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

int frq[4010];
double dp[4010][35];

int main()
{
	int b, n;

	scanf("%d %d", &b, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &frq[i]);
	}

	for (int i = 1; i <= n; i++) {
		for (int bcnt = 0; bcnt <= b; bcnt++) {
			dp[i][bcnt] = INF;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int bcnt = 0; bcnt < b; bcnt++) {
			int sum1 = 0;
			int sum2 = 0;
			for (int nxt = i + 1; nxt <= n; nxt++) {
				sum1 += frq[nxt];
				sum2 += frq[nxt] * frq[nxt];
				double avg = (double)sum1 / (nxt - i);
				double tmp = sum2 - 2 * avg * sum1 + avg * avg * (nxt - i);

				dp[nxt][bcnt + 1] = min(dp[nxt][bcnt + 1], dp[i][bcnt] + tmp);
			}
		}
	}

	printf("%.9lf\n", dp[n][b]);
	return 0;
}
