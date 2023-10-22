#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int height[1010];
int ans[1010];

int main()
{
	int n;
	int nowv, sum;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int l, h;
		scanf("%d %d", &l, &h);
		height[l] = h;
	}

	for (int i = 1; i <= 1000; i++) {
		ans[i] = INF;
	}

	nowv = 0;
	for (int i = 1; i <= 1000; i++) {
		nowv = max(nowv, height[i]);
		ans[i] = min(ans[i], nowv);
	}
	nowv = 0;
	for (int i = 1000; i >= 1; i--) {
		nowv = max(nowv, height[i]);
		ans[i] = min(ans[i], nowv);
	}

	sum = 0;
	for (int i = 1; i <= 1000; i++) {
		sum += ans[i];
	}
	printf("%d\n", sum);
	return 0;
}
