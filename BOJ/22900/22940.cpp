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
const double EPS = 1e-6;

int n;
double arr[10][10];

void pls(int from, double k, int to) {
	for (int i = 0; i <= n; i++) {
		arr[to][i] += arr[from][i] * k;
	}
}
void div(int from, double k) {
	for (int i = 0; i <= n; i++) {
		arr[from][i] /= k;
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= n; j++) {
			scanf("%lf", &arr[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		if (arr[i][i] == 0) {
			for (int j = i + 1; j < n; j++) {
				if (arr[j][i] != 0) {
					pls(j, 1, i);
					break;
				}
			}
		}
		div(i, arr[i][i]);

		for (int j = i + 1; j < n; j++) {
			pls(i, -arr[j][i], j);
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			pls(i, -arr[j][i], j);
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%d ", (int)(arr[i][n] + EPS));
	}
	return 0;
}
