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

	while (t--) {
		int n;
		double ans = 0.0;

		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			int x1, y1, x2, y2;
			double ang1, ang2, diff;
			
			scanf("%d %d", &x1, &y1);
			scanf("%d %d", &x2, &y2);
			ang1 = atan2(y1, x1);
			ang2 = atan2(y2, x2);
			
			if (ang1 > ang2) swap(ang1, ang2);
			diff = ang2 - ang1;
			if (diff > PI) diff = 2 * PI - diff;
			
			ans += diff / (2 * PI);
		}
		printf("%.5lf\n", ans);
	}
	return 0;
}
