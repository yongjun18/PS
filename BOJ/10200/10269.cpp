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

int leave[105];
int enter[105];
int stay[105];

int main()
{
	int c, n;
	int now, ans;

	scanf("%d %d", &c, &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &leave[i], &enter[i], &stay[i]);
	}

	now = 0;
	ans = 1;
	for (int i = 0; i < n; i++) {
		now -= leave[i];
		if (now < 0) {
			ans = 0;
			break;
		}
		now += enter[i];
		if (now > c) {
			ans = 0;
			break;
		}
		if (now < c && stay[i] > 0) {
			ans = 0;
			break;
		}
	}

	if (now != 0) ans = 0;
	if (stay[n - 1] > 0) ans = 0;

	printf("%s\n", ans ? "possible" : "impossible");
	return 0;
}
