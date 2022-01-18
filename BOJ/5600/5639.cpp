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

const int MX = 1000100;

int le[MX];
int ri[MX];
int up[MX];

int lo[MX];
int hi[MX];

void dfs(int x) {
	if (le[x] != 0) dfs(le[x]);
	if (ri[x] != 0) dfs(ri[x]);
	printf("%d\n", x);
}

int main()
{
	int root;
	int x, now;

	scanf("%d", &x);
	root = now = x;
	lo[now] = -INF;
	hi[now] = INF;

	while (scanf("%d", &x) > 0) {
		while (x < lo[now] || hi[now] < x) 
			now = up[now];

		if (x < now) {
			lo[x] = lo[now];
			hi[x] = now;

			up[x] = now;
			le[now] = x;
			now = x;
		}
		else {
			lo[x] = now;
			hi[x] = hi[now];

			up[x] = now;
			ri[now] = x;
			now = x;
		}
	}

	dfs(root);
	return 0;
}
