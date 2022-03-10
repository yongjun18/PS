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
#include <functional>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 100100;
int fenn, msb;
ll tree[MX];

void update(int x, ll diff) {
	while (x <= fenn) {
		tree[x] += diff;
		x += (x & -x);
	}
}

// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=pasdfq&logNo=221268429266
int get_kth(int k) {
	int ret = 0;
	for (int i = msb; i >= 1; i >>= 1) {
		if (ret + i <= fenn && tree[ret + i] < k) {
			k -= tree[ret + i];
			ret += i;
		}
	}
	return ret + 1;
}

int arr[305][305];
int ans[305][305];

int main()
{
	int m, n, k, w;
	int x, y, d;

	scanf("%d %d %d %d", &m, &n, &k, &w);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	fenn = k;
	msb = 1;
	while (msb * 2 <= fenn) msb *= 2;

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {
			update(arr[i][j] + 1, 1);
		}
	}
	x = 0; y = 0;
	d = 1;

	while (x + w <= m) {
		ans[x][y] = get_kth(w * w / 2 + 1) - 1;

		if (d == 1) {
			while (y + 1 + w <= n) {
				for (int i = 0; i < w; i++) {
					update(arr[x + i][y] + 1, -1);
					update(arr[x + i][y + w] + 1, 1);
				}
				y++;
				ans[x][y] = get_kth(w * w / 2 + 1) - 1;
			}
		}
		else {
			while (y - 1 >= 0) {
				for (int i = 0; i < w; i++) {
					update(arr[x + i][y + w - 1] + 1, -1);
					update(arr[x + i][y - 1] + 1, 1);
				}
				y--;
				ans[x][y] = get_kth(w * w / 2 + 1) - 1;
			}
		}

		for (int j = 0; j < w; j++) {
			update(arr[x][y + j] + 1, -1);
			update(arr[x + w][y + j] + 1, 1);
		}
		d ^= 1;
		x++;
	}
	
	for (int i = 0; i < m - (w - 1); i++) {
		for (int j = 0; j < n - (w - 1); j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
	return 0;
}
