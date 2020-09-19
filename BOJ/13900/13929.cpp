#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[100100];
vector< vector<int> > SCC;

int dfsn[100100];
int visit[100100];
int finish[100100];
int cnt = 0;
stack<int> st;

int snum[100100];
int scnt = 0;

int dfs(int x) {
	visit[x] = 1;
	dfsn[x] = cnt++;
	st.push(x);

	int minv = dfsn[x];
	for (int next : adj[x]) {
		if (!visit[next]) minv = min(minv, dfs(next));
		else if (!finish[next]) minv = min(minv, dfsn[next]);
	}

	if (minv == dfsn[x]) {
		vector<int> now_scc;
		while (1) {
			int top = st.top(); st.pop();
			snum[top] = scnt;

			now_scc.push_back(top);
			finish[top] = 1;
			if (top == x) break;
		}
		SCC.push_back(now_scc);
		scnt++;
	}
	return minv;
}

int get_SCC(int n) {
	for (int i = 0; i < n; i++) {
		if (!visit[i]) dfs(i);
	}
	return SCC.size();
}

int dp[100100][32];

int dfs2(int now, int bit){
	int &ret = dp[now][bit];
	if(ret != 0) return ret;
	ret = 1;

	for(int nxt : adj[now]){
		int order = 0;
		while(SCC[snum[nxt]][order] != nxt) order++;

		if(snum[now] == snum[nxt]){
			if((bit & (1 << order)) == 0)
				ret = max(ret, 1 + dfs2(nxt, bit | (1 << order)));
		}
		else ret = max(ret, 1 + dfs2(nxt, 1 << order));
	}
	return ret;
}

int main()
{
	int n, m, ans;

	scanf("%d %d", &n, &m);
	while(m--){
		int a, b;
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].push_back(b);
	}
	get_SCC(n);

	ans = 0;
	for(int i=0; i<n; i++){
		int order = 0;
		while(SCC[snum[i]][order] != i) order++;
		ans = max(ans, dfs2(i, 1 << order));
	}
	printf("%d\n", ans);
	return 0;
}
