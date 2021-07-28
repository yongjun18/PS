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
const ll INF = 1e15;
const int MOD = 1e9 + 7;

const int SHORT = 1;
const int BRIDG = 2;

struct Edge{
	int prev;
	int next;
	ll w;
	int idx;
};
struct QNode{
	int now;
	ll wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};
vector<ll> dijkstra(int n, int start, vector<Edge> adj[]){
	vector<ll> dist = vector<ll>(n, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({ start, 0 });

	while (pq.size()){
		int now = pq.top().now;
		ll wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]){
			int next = e.next;
			ll next_dist = wsum + e.w;
			if (dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({ next, next_dist });
			}
		}
	}
	return dist;
}

vector<Edge> eds;
vector<Edge> adjf[100100];
vector<Edge> adjr[100100];
vector<Edge> adjb[100100];

vector<ll> distf, distr;

int stat[100100];

int cnt = 0;
int dfsn[100100];
int visit[100100];
int minv[100100];

void dfs(int now, int idx){
	dfsn[now] = cnt++;
	visit[now] = 1;
	minv[now] = dfsn[now];

	for (Edge e : adjb[now]){
		if (idx == e.idx) continue;
		if (visit[e.next] == 0) dfs(e.next, e.idx);

		minv[now] = min(minv[now], minv[e.next]);
		if (minv[e.next] > dfsn[now]){
			stat[e.idx] |= BRIDG;
		}
	}
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		int u, v;
		ll w;
		scanf("%d %d %lld", &u, &v, &w);
		eds.push_back({ u, v, w, i });
		adjf[u].push_back({ u, v, w, i });
		adjr[v].push_back({ v, u, w, i });
	}
	distf = dijkstra(n + 1, 1, adjf);
	distr = dijkstra(n + 1, 2, adjr);

	for (int i = 1; i <= n; i++){
		for (Edge e : adjf[i]){
			if (distf[e.prev] + e.w + distr[e.next] == distf[2]){
				stat[e.idx] |= SHORT;
				adjb[e.prev].push_back({ e.prev, e.next, e.w, e.idx });
				adjb[e.next].push_back({ e.next, e.prev, e.w, e.idx });
			}
		}
	}
	dfs(1, -1);

	for (int i = 0; i < m; i++){
		if (stat[i] & SHORT){
			if (stat[i] & BRIDG) printf("SAD\n");
			else printf("SOSO\n");
		}
		else{
			int u = eds[i].prev;
			int v = eds[i].next;
			ll w = eds[i].w;
			if (distf[v] + w + distr[u] < distf[2]) printf("HAPPY\n");
			else printf("SOSO\n");
		}
	}

	return 0;
}
