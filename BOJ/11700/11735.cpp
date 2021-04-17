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

int rvis[1001000];
int cvis[1001000];

int main()
{
	int n, q;
	char c;
	int x;
	ll val;
	ll rsum, csum, rcnt, ccnt;

	scanf("%d %d", &n, &q);
	rsum = csum = rcnt = ccnt = 0;

	while (q--){
		scanf(" %c %d", &c, &x);
		val = (ll)x * n + (ll)n * (n + 1) / 2;

		if (c == 'R'){
			if (rvis[x]){
				printf("0\n");
				continue;
			}
			printf("%lld\n", val - csum - ccnt * x);
			rcnt++;
			rsum += x;
			rvis[x] = 1;
		}
		if (c == 'C'){
			if (cvis[x]){
				printf("0\n");
				continue;
			}
			printf("%lld\n", val - rsum - rcnt * x);
			ccnt++;
			csum += x;
			cvis[x] = 1;
		}

	}
	return 0;
}
