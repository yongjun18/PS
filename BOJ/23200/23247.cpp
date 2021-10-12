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

int n, m;
int arr[305][305];

int check(int x, int y, int len) {
	int sum = 0;
	for (int j = y; j < m; j++) {
		for (int i = 0; i < len; i++) {
			sum += arr[x + i][j];
		}
		if (sum == 10) return 1;
		if (sum > 10) return 0;
	}
	return 0;
}

int main()
{
	int ans = 0;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int x = 0; x < n; x++) {
		for (int y = 0; y < m; y++) {
			for (int len = 1; len <= 10; len++) {
				if (x + len > n) break;
				ans += check(x, y, len);
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}
