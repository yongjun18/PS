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

vector<int> fail;

void get_fail(char* s, int len){
	int match = 0;
	fail = vector<int>(len, 0);
	for (int last = 1; last < len; last++){
		while (s[last] != s[match] && match > 0)
			match = fail[match - 1];
		if (s[last] == s[match]) match++;
		fail[last] = match;
	}
}

char str[5010];
int dp[5010];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;

		scanf("%d", &n);
		scanf("%s", str + 1);

		dp[0] = 0;
		for (int i = 1; i <= n; i++){
			dp[i] = INF;
		}

		for (int i = 0; i <= n - 1; i++){
			if (dp[i] >= INF) continue;

			get_fail(str + i + 1, n - i);
			for (int j = 0; j < n - i; j++){
				if (fail[j] > 0){
					dp[i + 1 + j] = min(dp[i + 1 + j], dp[i] + 1);
				}
			}
		}

		printf("Case #%d\n", test);
		if (dp[n] >= INF) printf("0\n");
		else printf("%d\n", dp[n]);
	}

	return 0;
}
