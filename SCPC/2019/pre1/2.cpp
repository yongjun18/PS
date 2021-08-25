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

const double PI = acos(-1.0);

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int r, s, e, n;
		double ans;

		scanf("%d %d %d %d", &r, &s, &e, &n);
		ans = e - s;

		for (int i = 0; i < n; i++){
			int h;
			scanf("%*d %*d %d", &h);

			if (h >= r){
				double diff = (h - r) + (2 * PI * r / 4) - r;
				ans += 2 * diff;
			}
			else{
				double ang = asin((double)(r - h) / r);
				double diff = (PI / 2 - ang) * r - r * cos(ang);
				ans += 2 * diff;
			}
		}
		printf("Case #%d\n", test);
		printf("%.9lf\n", ans);
	}

	return 0;
}
