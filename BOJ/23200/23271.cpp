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

const int MX = 350;
const int CO = 110;

int arr[MX][MX];

int in_circle(int x, int y, int r, int nowx, int nowy) {
	return (x - nowx) * (x - nowx) + (y - nowy) * (y - nowy) <= r * r;
}

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, y, r;
		scanf("%d %d %d", &x, &y, &r);
		x *= 10;
		y *= 10;
		r *= 10;

		for (int i = x - r; i <= x + r; i++) {
			for (int j = y - r; j <= y + r; j++) {
				if (in_circle(x, y, r, i, j)) {
					arr[i + CO][j + CO] = 1;
				}
			}
		}
	}

	ans = 0;
	for (int i = 0; i < MX; i++) {
		for (int j = 0; j < MX; j++) {
			ans += arr[i][j];
		}
	}
	printf("%.3lf\n", (double)ans / 100);
	return 0;
}
