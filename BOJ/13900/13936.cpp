#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int O = 100005;
const int C = 100006;

vector<int> adj[100100];
vector<int> rev[100100];

int dist1[100100];
int disto[100100];
int distc[100100];

void add_edge(int u, int v){
	adj[u].push_back(v);
	rev[v].push_back(u);
}

void bfs(int n, int start, int dist[], vector<int> ad[]){
	vector<int> v1, v2;

	for(int i=1; i<=n; i++)
		dist[i] = INF;
	dist[start] = 0;
	v1.push_back(start);

	for(int t=1; v1.size() > 0; t++){
		for(int now : v1){
			for(int nxt : ad[now]){
				if(dist[nxt] < INF) continue;
				dist[nxt] = t;
				v2.push_back(nxt);
			}
		}
		swap(v1, v2);
		v2.clear();
	}
}

int main()
{
	int n, m, k;
	int ans;

	scanf("%d %d %d", &n, &m, &k);

	for(int i=0; i<m; i++){
		int x;
		scanf("%d", &x);
		add_edge(x, O);
	}
	for(int i=0; i<k; i++){
		int x;
		scanf("%d", &x);
		add_edge(x, C);
	}
	for(int i=1; i<=n; i++){
		int cnt;
		scanf("%d", &cnt);
		while(cnt--){
			int x;
			scanf("%d", &x);
			add_edge(i, x);
		}
	}

	bfs(n, 1, dist1, adj);
	bfs(n, O, disto, rev);
	bfs(n, C, distc, rev);

	ans = INF;
	for(int i=1; i<=n; i++){
		if(dist1[i] > n || disto[i] > n || distc[i] > n)
			continue;
		ans = min(ans, dist1[i] + disto[i]-1 + distc[i]-1);
	}

	if(ans > n)
		printf("impossible\n");
	else printf("%d\n", ans);
	return 0;
}
