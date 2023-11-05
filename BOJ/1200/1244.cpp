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

int arr[105];

int main()
{
	int n, m;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}

	scanf("%d", &m);
	while (m--) {
		int s, num;
		scanf("%d %d", &s, &num);

		if (s == 1) {
			for (int i = num; i <= n; i += num) {
				arr[i] ^= 1;
			}
		}
		else {
			int x, y;
			arr[num] ^= 1;
			x = num - 1;
			y = num + 1;
			while (1 <= x && y <= n) {
				if (arr[x] != arr[y]) break;
				arr[x] ^= 1;
				arr[y] ^= 1;
				x--; y++;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		printf("%d ", arr[i]);
		if (i % 20 == 0) printf("\n");
	}
	printf("\n");
	return 0;
}
