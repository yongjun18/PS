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

const int MX = 1000100;
int dpa[MX];
int dpb[MX];
int asum[MX];
int bsum[MX];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int a, b, c;
		int n, k;
		int l, r;
		
		scanf("%d %d %d", &a, &b, &c);

		printf("Case #%d\n", test);
		while (c--){
			scanf("%d %d", &n, &k);
			for (int i = 0; i < n + 5; i++){
				dpa[i] = dpb[i] = 0;
				asum[i] = bsum[i] = 0;
			}

			for (int i = n - 1; i >= 1; i--){
				l = min(i + b, n);
				r = min(i + b * k, n);
				if (bsum[l] - bsum[r + 1] == 0){
					dpa[i] = 1;
				}
				asum[i] = asum[i + 1] + dpa[i];

				l = min(i + a, n);
				r = min(i + a * k, n);
				if (asum[l] - asum[r + 1] == 0){
					dpb[i] = 1;
				}
				bsum[i] = bsum[i + 1] + dpb[i];
			}

			l = min(a, n);
			r = min(a * k, n);
			if (asum[l] - asum[r + 1] > 0){
				printf("a");
			}
			else{
				printf("b");
			}
		}
		printf("\n");
	}
	return 0;
}
