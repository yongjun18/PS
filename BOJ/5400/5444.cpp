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

int arr[510];
int dp[2][100100];

int main()
{
	int t;

	scanf("%d", &t);
	while (t--) {

		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
		}
		for (int j = 0; j < m; j++) {
			dp[0][j] = dp[1][j] = -1;
		}
		dp[0][0] = 0;

		for (int i = 1; i <= n; i++) {
			int now = i & 1;
			int pv = !now;
			
			for (int j = 0; j < m; j++) {
				dp[now][j] = dp[pv][j];
			}
			for (int j = 0; j < m; j++) {
				if (dp[pv][j] == -1) continue;
				int modv = (j + arr[i]) % m;
				dp[now][modv] = max(dp[now][modv], dp[pv][j] + 1);
			}
		}
		printf("%d\n", dp[n & 1][0]);

	}
	return 0;
}
