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

int ans[15];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x, cnt0;
		scanf("%d", &x);

		cnt0 = 0;
		for (int j = 1; j <= n; j++) {
			if (cnt0 >= x && ans[j] == 0) {
				ans[j] = i;
				break;
			}
			if (ans[j] == 0) {
				cnt0++;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
