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

int k, n;
int l[9];
int arr[9][9];
int last[9];
int dp[1000100];

int dfs(int x, int y){
	if (x > k) return 1;
	if (y > l[x]) return dfs(x + 1, 1);

	int ret = 0;
	int key = 0;
	
	if (x == 3 && y == 1){
		for (int i = 1; i <= l[x - 1]; i++){
			key *= 7;
			key += arr[x - 1][i] - 1;
		}
		if (dp[key] != -1) return dp[key];
	}

	int lo = max(arr[x - 1][y] + 1, arr[x][y - 1]);
	int hi = min(n, n - (last[y] - x));
	for (int i = lo; i <= hi; i++){
		arr[x][y] = i;
		ret += dfs(x, y + 1);
	}

	if (x == 3 && y == 1) dp[key] = ret;
	return ret;
}

int main()
{
	while (scanf("%d", &k) > 0){
		for (int i = 1; i <= k; i++){
			scanf("%d", &l[i]);
			for (int j = 1; j <= l[i]; j++){
				last[j] = i;
			}
		}
		scanf("%d", &n);

		memset(dp, -1, sizeof(dp));

		printf("%d\n", dfs(1, 1));
	}
	return 0;
}
