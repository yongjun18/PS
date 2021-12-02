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
	int n1, n2;
	int ans = INF;
	int ans1, ans2, ans3;

	scanf("%d %d", &n1, &n2);

	ans1 = n2 - n1;
	ans2 = n2 - (n1 + 360);
	ans3 = (n2 + 360) - n1;

	if (abs(ans) > abs(ans1)) ans = ans1;
	if (abs(ans) > abs(ans2)) ans = ans2;
	if (abs(ans) > abs(ans3)) ans = ans3;
	if (ans == -180) ans *= -1;

	printf("%d\n", ans);
	return 0;
}
