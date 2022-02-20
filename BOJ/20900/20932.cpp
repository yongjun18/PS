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

int arr[20];
ll dp[16][70100][10][10];

int main()
{
	int n;
	ll total, success;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	for (int mod = 1; mod <= 9; mod++) {
		dp[0][0][mod][0] = 1;
	}

	for (int i = 0; i <= n - 2; i++) {
		for (int state = 0; state < (1 << n); state++) {
			for (int mod = 1; mod <= 9; mod++) {
				for (int modv = 0; modv < mod; modv++) {
					if (dp[i][state][mod][modv] == 0) continue;

					for (int k = 0; k < n; k++) {
						if (state & (1 << k)) continue;
						int nstate = state + (1 << k);
						ll now = arr[k];
						for (int t = 0; t < i; t++) now *= 10;
						int nmodv = (modv + (now % mod)) % mod;

						dp[i + 1][nstate][mod][nmodv] += dp[i][state][mod][modv];
					}
				}
			}
		}
	}

	total = 1;
	for (int i = 1; i <= n; i++) total *= i;

	success = 0;
	for (int i = 0; i < n; i++) {
		int state = ((1 << n) - 1) ^ (1 << i);
		success += dp[n - 1][state][arr[i]][0];
	}
	printf("%.9lf\n", (double)success / total);
	return 0;
}
