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

const int MX = 20;

vector<int> adj[100100];
int dp[100100][MX + 1];

void dfs(int now, int p){
	for (int nxt : adj[now]){
		if (nxt == p) continue;
		dfs(nxt, now);
	}

	for (int i = 1; i <= MX; i++){
		dp[now][i] = i;
	}
	for (int nxt : adj[now]){
		if (nxt == p) continue;
		for (int i = 1; i <= MX; i++){
			int minv = INF;
			for (int j = 1; j <= MX; j++){
				if (i == j) continue;
				minv = min(minv, dp[nxt][j]);
			}
			dp[now][i] += minv;
		}
	}
}

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, -1);

	ans = INF;
	for (int i = 1; i <= MX; i++){
		ans = min(ans, dp[1][i]);
	}
	printf("%d\n", ans);
	return 0;
}
