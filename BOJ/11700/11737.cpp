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

const int BRD = -1;
const int MX = 50010;

int n, m;

struct Edge{
	int fr, to;
	int type;
};
vector<Edge*> adj[MX];
int visit[MX];
int depth[MX];
vector<Edge*> st;

int dp[MX];
int dp2[MX];

int ccnt = 0;
int csiz[MX];
ll exsum[MX];
int adjb[MX];

ll ans = 0;
ll presum = 0;

void dfs(int v, int h){
	for (Edge* e : adj[v]){
		if (e->to == h) continue;
		if (visit[e->to]){
			if (depth[e->to] < depth[v]){
				ccnt++;
				for (int i = depth[e->to]; i < depth[v]; i++){
					st[i]->type = ccnt;
				}
				csiz[ccnt] = depth[v] - depth[e->to] + 1;
			}
		}
		else{
			visit[e->to] = 1;
			depth[e->to] = depth[v] + 1;
			e->type = BRD;
			st.push_back(e);
			dfs(e->to, v);
			st.pop_back();
		}
	}
}

void dfs2(int v, int type){
	dp[v] = 1;

	for (Edge* e : adj[v]){
		if (e->type == 0) continue;
		dfs2(e->to, e->type);
		dp[v] += dp[e->to];
	}
	if (type == BRD){
		ll up = n - dp[v];
		ans += up * dp[v] - 1;
	}
}

void dfs3(int v, int h, int type){
	for (Edge* e : adj[v]){
		if (e->type == 0) continue;
		dfs3(e->to, v, e->type);

		if (e->type == BRD){
			dp2[v] += dp2[e->to] + 1;
		}
	}
	if (type > 0 || h == -1){
		set<int> adjc;
		int vcnt = dp2[v] + 1;
		ll tmp = (ll)vcnt * (vcnt - 1) / 2 - vcnt + 1;

		if (type > 0){
			adjc.insert(type);
			adjb[type] += dp2[v];
			exsum[type] += tmp;
		}
		for (Edge* e : adj[v]){
			if (e->type > 0 && adjc.find(e->type) == adjc.end()){
				adjc.insert(e->type);
				adjb[e->type] += dp2[v];
				exsum[e->type] += tmp;
			}
		}
		presum += tmp;
	}
}

void dfs4(int v, int dp2v, int type){
	dp2v = max(dp2v, dp2[v]);

	for (Edge* e : adj[v]){
		if (e->type == 0) continue;

		if (e->type > 0){
			if (type == BRD){
				int vcnt = dp2v + 1;
				exsum[e->type] += (ll)vcnt * (vcnt - 1) / 2 - vcnt + 1;
				adjb[e->type] += dp2v;
			}
			dfs4(e->to, 0, e->type);
		}
		else{
			dfs4(e->to, dp2v, e->type);
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	while (m--){
		int k, pv;
		scanf("%d", &k);
		pv = -1;
		for (int i = 0; i < k; i++){
			int x;
			scanf("%d", &x);
			if (pv != -1){
				Edge* ef = new Edge();
				Edge* er = new Edge();
				*ef = { pv, x, 0 };
				*er = { x, pv, 0 };
				adj[pv].push_back(ef);
				adj[x].push_back(er);
			}
			pv = x;
		}
	}
	visit[1] = 1;
	dfs(1, -1);
	dfs2(1, 0);
	dfs3(1, -1, 0);
	dfs4(1, dp2[1], 0);

	for (int i = 1; i <= ccnt; i++){
		int vcnt = csiz[i] + adjb[i];
		ans += csiz[i] * ((ll)vcnt * (vcnt - 1) / 2 - vcnt + presum - exsum[i]);
	}
	printf("%lld\n", ans);

	return 0;
}
