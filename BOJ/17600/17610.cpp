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

int visit[2600100];
int arr[20];
int sign[20];

void dfs(int now, int n) {
	if (now >= n) {
		int res = 0;
		for (int i = 0; i < n; i++) {
			res += sign[i] * arr[i];
		}
		if (res > 0) visit[res] = 1;
		return;
	}

	sign[now] = 0;
	dfs(now + 1, n);

	sign[now] = 1;
	dfs(now + 1, n);

	sign[now] = -1;
	dfs(now + 1, n);
}

int main()
{
	int n;
	int sum, ans;

	scanf("%d", &n);
	sum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];
	}
	
	dfs(0, n);
	ans = 0;
	for (int i = 1; i <= sum; i++) {
		if (visit[i] == 0) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
