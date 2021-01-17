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
const ll INF = 1e13;
const int MOD = 1e9 + 7;

const int MX = 4300100;
const int VER = 2100;

int num(int v, int order){
	return v * VER + order;
}

struct Edge{ int next; ll w; };
vector<Edge> adj[VER];
void add_edge(int u, int v, ll w){
	adj[u].push_back({ v, w });
}

ll dist[MX];
vector<int> pv[MX];

void build(int n){
	for (int i = 0; i < MX; i++){
		dist[i] = INF;
	}
	dist[num(1, 0)] = 0;

	for (int i = 0; i < n; i++){
		for (int j = 1; j <= n; j++){
			int now = num(j, i);
			if (dist[now] >= INF) continue;

			for (Edge e : adj[j]){
				int nxt = num(e.next, i + 1);
				ll ndist = dist[now] + e.w;
				if (dist[nxt] > ndist){
					dist[nxt] = ndist;
					pv[nxt].clear();
				}
				if (dist[nxt] == ndist){
					pv[nxt].push_back(now);
				}
			}
		}
	}
}

int visit[MX];
int used[VER];

void dfs(int now){
	visit[now] = 1;
	used[now / VER] = 1;

	for (int nxt : pv[now]){
		if (visit[nxt] == 0){
			dfs(nxt);
		}
	}
}

int check(int n, int x){
	double lb = 0;
	double ub = INF;
	ll d = dist[num(n, x)];

	if (d >= INF) return 0;

	for (int i = 1; i < x; i++){
		ll di = dist[num(n, i)];
		if (di >= INF) continue;
		ub = min(ub, (double)(di - d) / (x - i));
	}
	for (int i = x + 1; i <= n; i++){
		ll di = dist[num(n, i)];
		if (di >= INF) continue;
		lb = max(lb, (double)(d - di) / (i - x));
	}

	if (lb <= ub) return 1;
	else return 0;
}

int main()
{
	int n, m;
	int cnt;

	scanf("%d %d", &n, &m);
	while (m--){
		int x, y;
		ll w;
		scanf("%d %d %lld", &x, &y, &w);
		add_edge(x, y, w);
		add_edge(y, x, w);
	}
	build(n);

	for (int i = 1; i <= n; i++){
		if (check(n, i)){
			dfs(num(n, i));
		}
	}

	cnt = 0;
	for (int i = 1; i <= n; i++){
		if (used[i] == 0){
			cnt++;
		}
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++){
		if (used[i] == 0){
			printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}
