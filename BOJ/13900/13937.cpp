#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Edge {
	int from, to, capacity, flow;
	Edge* reverse;
};

vector<Edge*> adj[6200];
int level[6200];
int work[6200];

void add_edge(int u, int v, int capacity) {
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { u, v, capacity, 0, er };
	*er = { v, u, 0, 0, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int bfs(int source, int sink) {
	memset(level, -1, sizeof(level));
	level[source] = 0;

	queue<int> q;
	q.push(source);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		for (Edge* e : adj[now]) {
			if (level[e->to] == -1 && e->capacity - e->flow > 0) {
				level[e->to] = level[now] + 1;
				q.push(e->to);
			}
		}
	}
	return (level[sink] != -1);
}

int dfs(int now, int dest, int flow) {
	if (now == dest) return flow;

	for (int &i = work[now]; i < adj[now].size(); i++) {
		Edge* e = adj[now][i];
		if (level[e->to] == level[now] + 1 && e->capacity - e->flow > 0) {
			int amount = dfs(e->to, dest, min(e->capacity - e->flow, flow));
			if (amount > 0) {
				e->flow += amount;
				e->reverse->flow -= amount;
				return amount;
			}
		}
	}
	return 0;
}

int dinic(int source, int sink) {
	int total_flow = 0;
	while (bfs(source, sink)) {
		memset(work, 0, sizeof(work));
		while (1) {
			int flow = dfs(source, sink, INF);
			if (flow == 0) break;
			total_flow += flow;
		}
	}
	return total_flow;
}

const int S = 0;
const int T = 191;
const int SEN = 0;
const int QIN = 100;
const int QOUT = 130;
const int LINK = 160;
const int LAYER = 200;

int que[105];
int cap[35];

int main()
{
	int n, q, s;
	int sum = 0;
	int flow;

	scanf("%d %d %d", &n, &q, &s);
	for(int i=1; i<=s; i++){
		scanf("%d", &que[i]);
	}
	for(int i=1; i<=q; i++){
		scanf("%d", &cap[i]);
	}

	for(int i=1; i<=s; i++){
		for(int l=0; l<n; l++){
			add_edge(LAYER*l + SEN+i, LAYER*l + QIN+que[i], INF);
		}
	}
	for(int i=1; i<=q; i++){
		for(int l=0; l<n; l++){
			add_edge(LAYER*l + QIN+i, LAYER*l + QOUT+i, cap[i]);
			if(l<n-1)
				add_edge(LAYER*l + QOUT+i, LAYER*(l+1) + QIN+i, INF);

			add_edge(LAYER*l + QOUT+i, LINK+l+1, INF);
		}
	}

	for(int i=1; i<=n; i++){
		int d, gen;
		scanf("%d", &d);

		for(int j=1; j<=s; j++){
			scanf("%d", &gen);
			add_edge(S, LAYER*(i-1) + SEN+j, gen);
			sum += gen;
		}
		add_edge(LINK+i, T, d);
	}

	flow = dinic(S, T);
	if(flow >= sum) printf("possible\n");
	else printf("impossible\n");
	return 0;
}
