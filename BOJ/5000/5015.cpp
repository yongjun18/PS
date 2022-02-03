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

char p[105];
char str[105];
int dp[105][105];

int main()
{
	int n;
	int plen;
	int slen;

	scanf("%s", p);
	plen = strlen(p);

	scanf("%d", &n);
	while (n--) {
		scanf("%s", str);
		slen = strlen(str);

		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;

		for (int i = 0; i <= plen; i++) {
			for (int j = 0; j <= slen; j++) {
				if (dp[i][j] == 0) continue;

				if (p[i] == '*') {
					for (int k = j; k <= slen; k++) {
						dp[i + 1][k] = 1;
					}
				}
				else if (i < plen && j < slen && p[i] == str[j]) {
					dp[i + 1][j + 1] = 1;
				}
			}
		}
		if (dp[plen][slen]) {
			printf("%s\n", str);
		}
	}

	return 0;
}
