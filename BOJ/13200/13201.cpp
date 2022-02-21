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

char code[105][5];
int arr[105][105];
vector<int> adj[105];

long double prob[105][105];
long double dp[1050][105];

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int n, k;
		int start = -1;
		int ans;

		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			scanf("%s", code[i]);
			if (strcmp(code[i], "ICN") == 0) start = i;
			adj[i].clear();
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &arr[i][j]);
				if (arr[i][j] > 0) adj[i].push_back(j);
			}
		}

		for (int i = 0; i < n; i++) {
			int sum = 0;
			for (int j = 0; j < n; j++) {
				sum += arr[i][j];
			}
			for (int j = 0; j < n; j++) {
				prob[i][j] = (double)arr[i][j] / sum;
			}
		}

		for (int i = 0; i <= k; i++) {
			for (int j = 0; j < n; j++) {
				dp[i][j] = 0;
			}
		}
		dp[0][start] = 1;

		for (int i = 0; i < k; i++) {
			for (int j = 0; j < n; j++) {
				if (dp[i][j] == 0) continue;
				for (int nxt : adj[j]) {
					dp[i + 1][nxt] = max(dp[i + 1][nxt], dp[i][j] * prob[j][nxt]);
				}
			}
		}

		ans = 0;
		for (int i = 1; i < n; i++) {
			if (dp[k][i] > dp[k][ans]) {
				ans = i;
			}
		}
		printf("%s\n", code[ans]);
	}

	return 0;
}
