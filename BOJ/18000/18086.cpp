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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

double arr[505];
double ans[505];

int main()
{
	int n, k;
	double anssum;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++){
		scanf("%lf", &arr[i]);
	}

	if (k == 1){
		for (int i = 0; i < n; i++){
			printf("%.9lf\n", 100.0 / n);
		}
	}
	else{
		for (int i = 0; i < n; i++){
			int cn = n - 2;
			int cr = k - 2;
			double ncr = 1;
			double chance = arr[i];
			double chsum = chance * ncr;
			double ncrsum = ncr;

			for (int j = (i - 1 + n) % n; ; j = (j - 1 + n) % n){
				chance += arr[j];
				if (cn - cr == 0) break;
				ncr *= (double)(cn - cr) / cn;
				cn--;
				chsum += chance * ncr;
				ncrsum += ncr;
			}
			ans[i] = chsum / ncrsum;
		}

		anssum = 0;
		for (int i = 0; i < n; i++){
			anssum += ans[i];
		}
		for (int i = 0; i < n; i++){
			ans[i] = ans[i] * 100.0 / anssum;
		}
		for (int i = 0; i < n; i++){
			printf("%.9lf ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}
