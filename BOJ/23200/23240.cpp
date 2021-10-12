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

int ans = 0;
char color[30];
int num[30];
int mov[30];
int pos[30];

void solve(int from, int mid, int to, int siz) {
	if (siz <= 0) return;
	solve(from, to, mid, siz - 1);
	mov[siz]++;
	pos[siz] = to;
	ans += num[siz];
	solve(mid, from, to, siz - 1);
}

int main()
{
	int m;

	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf(" %c %d", &color[i], &num[i]);
		pos[i] = 1;
	}

	for (int i = m; i >= 1; i--) {
		int now = pos[i];
		int ot;
		int dest = 3;

		if (now == 1) ot = 2;
		else ot = 1;

		if (color[i] == 'G' || num[i] == 1 ||
			(color[i] == 'R' && mov[i] % 2 == 0) ||
			(color[i] == 'B' && mov[i] % 2 == 1)) {
			solve(now, dest, ot, i - 1);
			mov[i]++;
			pos[i] = dest;
			ans += num[i];
		}
		else {
			solve(now, ot, dest, i - 1);
			mov[i]++;
			pos[i] = ot;
			ans += num[i];

			solve(dest, ot, now, i - 1);
			mov[i]++;
			pos[i] = dest;
			ans += num[i];

			if (i == 1) ans--;
		}
	}
	printf("%d\n", ans);
	return 0;
}
