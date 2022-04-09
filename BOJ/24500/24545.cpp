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

vector<int> adj[100100];
int down[100100][3];
int up[100100];

void dfs1(int now, int pv) {
	vector<int> tmp;
	for (int i = 0; i < 3; i++) {
		tmp.push_back(0);
	}

	for (int nxt : adj[now]) {
		if (nxt == pv) continue;
		dfs1(nxt, now);
		tmp.push_back(down[nxt][0] + 1);
	}
	sort(tmp.begin(), tmp.end());

	for (int i = 0; i < 3; i++) {
		down[now][i] = *(tmp.rbegin() + i);
	}
}

void dfs2(int now, int pv) {
	for (int nxt : adj[now]) {
		if (nxt == pv) continue;
		up[nxt] = up[now] + 1;

		int maxi = 0;
		if (down[now][maxi] == down[nxt][0] + 1) maxi++;
		up[nxt] = max(up[nxt], down[now][maxi] + 1);
		
		dfs2(nxt, now);
	}
}

int check(int a, int b, int c) {
	if (a == 0 || b == 0 || c == 0) return 0;
	return a + b + c + 1;
}

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs1(1, -1);
	dfs2(1, -1);

	ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = max(ans, check(up[i], down[i][0], down[i][1]));
		ans = max(ans, check(down[i][0], down[i][1], down[i][2]));
	}
	printf("%d\n", ans);
	return 0;
}
