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


int main()
{
	int x1, y1, x2, y2;
	double ans;

	scanf("%d %d", &x1, &y1);
	scanf("%d %d", &x2, &y2);
	ans = hypot(x1 - x2, y1 - y2);

	scanf("%d %d", &x1, &y1);
	scanf("%d %d", &x2, &y2);
	ans = max(ans, hypot(x1 - x2, y1 - y2));

	printf("%.9lf\n", ans);
	return 0;
}
