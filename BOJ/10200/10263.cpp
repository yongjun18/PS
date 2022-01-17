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

int arr[100100];

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n + 1);

	ans = INF;
	for (int i = 0; i <= n; i++) {
		ans = min(ans, arr[i] + n - i);
	}
	printf("%d\n", ans);
	return 0;
}
