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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
ll l;

struct Edge{
	int to;
	ll w;
};
vector<Edge> adj[200100];

int st[200100];
ll depth[200100];

int check[200100];
int dp[200100];
int siz[200100];

void dfs(int now, int v){
	int pos = lower_bound(depth, depth + now, depth[now] - l) - depth;
	if (pos > 0){
		check[st[pos - 1]]++;
	}
	for (Edge e : adj[v]){
		st[now + 1] = e.to;
		depth[now + 1] = depth[now] + e.w;
		dfs(now + 1, e.to);
	}
}

void dfs2(int v){
	siz[v] = 1;
	dp[v] = check[v];
	
	for (Edge e : adj[v]){
		dfs2(e.to);
		siz[v] += siz[e.to];
		dp[v] += dp[e.to];
	}
}

int main()
{
	scanf("%d %lld", &n, &l);
	for (int i = 2; i <= n; i++){
		int p;
		ll w;
		scanf("%d %lld", &p, &w);
		adj[p].push_back({ i, w });
	}

	st[0] = 1;
	depth[0] = 0;
	dfs(0, 1);
	dfs2(1);

	for (int i = 1; i <= n; i++){
		printf("%d\n", siz[i] - dp[i]);
	}
	return 0;
}
