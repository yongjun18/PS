#include <bits/stdc++.h>
using namespace std;

int n, k;
int nxt[160];
int vis[160];

int dfs(int now, int depth){
	if(vis[now]) return 0;
	if(now == k) return depth;
	vis[now] = 1;
	return dfs(nxt[now], depth + 1);
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i=0; i<n; i++){
		scanf("%d", &nxt[i]);
	}
	
	printf("%d\n", dfs(0, 1) - 1);
	return 0;
}
