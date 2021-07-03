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

ll arr[510];
ll minv[510][510];
ll dp[510][510];

ll memo(int x, int y){
	if (x == 0) return 0;
	if (x <= y) return 0;
	if (y == 0) return INF;
	ll &ret = dp[x][y];
	if (ret != -1) return ret;

	ret = INF;
	for (int i = 1; i <= x; i++){
		ret = min(ret, memo(x - i, y - 1) + minv[x - i + 1][x]);
	}
	return ret;
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;

		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++){
			scanf("%lld", &arr[i]);
		}
		sort(arr + 1, arr + 1 + n);

		for (int i = 1; i <= n; i++){
			minv[i][i] = 0;
			for (int j = i + 1; j <= n; j++){
				minv[i][j] = minv[i][j - 1];
				if ((j - i) % 2 == 1) minv[i][j] += arr[j] - arr[(i + j - 1) / 2];
				else minv[i][j] += arr[j] - arr[(i + j) / 2];
			}
		}

		for (int i = 0; i < n + 5; i++){
			for (int j = 0; j < m + 5; j++){
				dp[i][j] = -1;
			}
		}

		printf("Case #%d\n", test);
		printf("%lld\n", memo(n, m));
	}

	return 0;
}
