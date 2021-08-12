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

int s[55];
int t[55];
int p[55];

int dp[1010][1010];
int lpnt[1010][1010];
int cnt[1010][1010];

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d %d %d", &s[i], &t[i], &p[i]);
	}

	dp[1][1] = 1;
	for (int i = 0; i < n; i++){
		if (s[i] == 1 || t[i] == 1){
			lpnt[1][1] += p[i];
			cnt[1][1]++;
		}
	}

	for (int i = 1; i <= 1000; i++){
		for (int j = 1; j <= 1000; j++){
			if ((i > 1 && dp[i - 1][j] && lpnt[i - 1][j] > 0) ||
				(j > 1 && dp[i][j - 1] && lpnt[i][j - 1] > 0)){
				dp[i][j] = 1;
				lpnt[i][j] = (1 - i) + (1 - j);
				for (int k = 0; k < n; k++){
					if (s[k] <= i || t[k] <= j){
						lpnt[i][j] += p[k];
						cnt[i][j]++;
					}
				}
			}
		}
	}

	ans = 0;
	for (int i = 1; i <= 1000; i++){
		for (int j = 1; j <= 1000; j++){
			ans = max(ans, cnt[i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
