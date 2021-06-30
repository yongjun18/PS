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

int h[105][105];
int wat[105][105];
int dp[105][105][15];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m, k;

		scanf("%d %d %d", &m, &n, &k);
		for (int i = 0; i <= n; i++){
			for (int j = 0; j <= m; j++){
				scanf("%d", &h[i][j]);
				if (h[i][j] < 0){
					wat[i][j] = 1;
					h[i][j] *= -1;
				}
				else{
					wat[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < n + 5; i++){
			for (int j = 0; j < m + 5; j++){
				for (int cnt = 0; cnt < k + 5; cnt++){
					dp[i][j][cnt] = INF;
				}
			}
		}
		dp[0][0][0] = 0;

		for (int i = 0; i <= n; i++){
			for (int j = 0; j <= m; j++){
				for (int cnt = 0; cnt <= k; cnt++){
					if (i > 0){
						int diff = abs(h[i][j] - h[i - 1][j]);
						dp[i][j][cnt] = min(dp[i][j][cnt], dp[i - 1][j][cnt] + diff);
						if (wat[i][j] == 1 && cnt > 0){
							dp[i][j][cnt] = min(dp[i][j][cnt], dp[i - 1][j][cnt - 1] + diff);
						}
					}
					if (j > 0){
						int diff = abs(h[i][j] - h[i][j - 1]);
						dp[i][j][cnt] = min(dp[i][j][cnt], dp[i][j - 1][cnt] + diff);
						if (wat[i][j] == 1 && cnt > 0){
							dp[i][j][cnt] = min(dp[i][j][cnt], dp[i][j - 1][cnt - 1] + diff);
						}
					}
				}
			}
		}
		printf("Case #%d\n", test);
		printf("%d\n", dp[n][m][k]);
	}

	return 0;
}
