#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 2e5;

vector<int> adj[MX];
vector<ll> cost[MX];

int parent[MX][18];
ll dist[MX][18];
int depth[MX];

int check[MX];
int siz[MX];
int sum[MX];

void add_edge(int u, int v, ll c) {
	adj[u].push_back(v);
	adj[v].push_back(u);
	cost[u].push_back(c);
	cost[v].push_back(c);
}

void dfs(int now) {
	for (int i=0; i<adj[now].size(); i++) {
		int next = adj[now][i];
		ll c = cost[now][i];
		if (depth[next] != -1) continue;

		depth[next] = depth[now] + 1;
		parent[next][0] = now;
		dist[next][0] = c;
		dfs(next);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));
	for(int i=0; i<n; i++){
		for(int j=0; j<18; j++)
			dist[i][j] = INF;
	}
	depth[0] = 0;
	dfs(0);

	for (int k = 0; k < 18 - 1; k++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][k] != -1){
				parent[i][k + 1] = parent[parent[i][k]][k];
				dist[i][k + 1] = dist[i][k] + dist[parent[i][k]][k];
			}
		}
	}
}

int getp(int u, ll d) {
	ll dsum = 0;
	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		ll nowd = dist[u][k];
		if(ancu != -1 && dsum + nowd <= d){
			dsum += nowd;
			u = ancu;
		}
	}
	return u;
}

void dfs2(int v, int p){
	siz[v] = 1;
	sum[v] = check[v];
	for(int next : adj[v]){
		if(next == p) continue;
		dfs2(next, v);
		siz[v] += siz[next];
		sum[v] += sum[next];
	}
}

int main()
{
	int n;
	ll l;
	scanf("%d %lld", &n, &l);

	for(int i=1; i<n; i++){
		int p;
		ll c;
		scanf("%d %lld", &p, &c); p--;
		add_edge(i, p, c);
	}
	build(n);

	for(int i=0; i<n; i++){
		int p = getp(i, l);
		if(parent[p][0] != -1)
			check[parent[p][0]]++;
	}
	dfs2(0, 0);

	for(int i=0; i<n; i++)
		printf("%d\n", siz[i] - sum[i]);
	return 0;
}
