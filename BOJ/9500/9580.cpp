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

double prob[3010][3010];

int main()
{
	int n;
	ll a, b;
	double ansa, ansb;

	scanf("%d %lld %lld", &n, &a, &b);

	prob[0][0] = 1;
	for (int x = 0; x <= n; x++){
		for (int y = 0; y <= n; y++){
			if (x + y >= n) continue;

			ll rx = a + 1 - x;
			ll ry = b - y;
			if (x + 1 <= a){
				prob[x + 1][y] += prob[x][y] * (rx * 2 - 2) / (rx * 2 + ry);
			}
			if (y + 1 <= b){
				prob[x][y + 1] += prob[x][y] * (ry) / (rx * 2 + ry);
			}
		}
	}
	ansa = 0;
	for (int x = 0; x <= n; x++){
		for (int y = 0; y <= n; y++){
			if (x + y >= n) continue;
			ll rx = a + 1 - x;
			ll ry = b - y;
			if (rx < 0 || ry < 0 || rx + ry == 0) continue;
			ansa += prob[x][y] * 2 / (rx * 2 + ry);
		}
	}

	memset(prob, 0, sizeof(prob));
	prob[0][0] = 1;
	for (int x = 0; x <= n; x++){
		for (int y = 0; y <= n; y++){
			if (x + y >= n) continue;

			ll rx = a - x;
			ll ry = b + 1 - y;
			if (x + 1 <= a){
				prob[x + 1][y] += prob[x][y] * (rx * 2) / (rx * 2 + ry);
			}
			if (y + 1 <= b){
				prob[x][y + 1] += prob[x][y] * (ry - 1) / (rx * 2 + ry);
			}
		}
	}
	ansb = 0;
	for (int x = 0; x <= n; x++){
		for (int y = 0; y <= n; y++){
			if (x + y >= n) continue;
			ll rx = a - x;
			ll ry = b + 1 - y;
			if (rx < 0 || ry < 0 || rx + ry == 0) continue;
			ansb += prob[x][y] / (rx * 2 + ry);
		}
	}
	printf("%.15lf\n", ansa);
	printf("%.15lf\n", ansb);

	return 0;
}
