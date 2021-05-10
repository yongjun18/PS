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

vector<int> adj[1010];

double x[1010];
double y[1010];
double nxty = 0;

void dfs(int now, int h){
	if (h == -1){
		x[now] = 0;
		y[now] = 0;
		nxty = 1.0 / 10000;
	}
	else{
		x[now] = x[h] + sqrt(1 - (nxty - y[h]) * (nxty - y[h]));
		y[now] = nxty;
		nxty += 1.0 / 10000;
	}
	
	for (int nxt : adj[now]){
		if (nxt == h) continue;
		dfs(nxt, now);
	}
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}

	dfs(1, -1);

	for (int i = 1; i <= n; i++){
		printf("%.9lf %.9lf\n", x[i], y[i]);
	}
	return 0;
}
