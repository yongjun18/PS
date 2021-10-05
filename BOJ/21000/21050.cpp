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
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 200100;

int capacity[MX];
int current[MX];
vector<int> adj[MX];

int dfs(int now, int need) {
	int ret, nowv;

	nowv = max(need - current[now], capacity[now] - current[now]);
	ret = nowv;
	for (int nxt : adj[now]) {
		ret = min(ret, dfs(nxt, nowv));
	}
	return ret;
}

int main()
{
	int n, w;

	scanf("%d %d", &n, &w);
	for (int i = 1; i <= n; i++) {
		int p;
		scanf("%d %d %d", &p, &capacity[i], &current[i]);
		adj[p].push_back(i);
	}
	current[0] = 0;
	capacity[0] = w;

	printf("%d\n", dfs(0, 0));

	return 0;
}
