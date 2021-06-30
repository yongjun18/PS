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

const int S = 0;
const int T = 305;
const int SHOE = 0;
const int TIME = 201;

const int MX = 310;
const int PMX = 100;

struct Edge {
	int from, to, capacity, flow;
	Edge* reverse;
};

vector<Edge*> adj[MX];
int level[MX];
int work[MX];

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

int power[PMX];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, k;
		int psum, res;

		for (int i = 0; i < MX; i++){
			for (Edge* e : adj[i]) free(e);
			adj[i].clear();
		}
		for (int i = 0; i < PMX; i++){
			power[i] = 0;
		}
		psum = 0;

		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++){
			int a, f, p;
			scanf("%d %d %d", &a, &f, &p);

			psum += p;
			add_edge(S, i + SHOE, p);
			for (int j = a; j < f; j++){
				add_edge(i + SHOE, j + TIME, 1);
			}
		}

		for (int i = 1; i <= k; i++){
			int s, e;
			scanf("%d %d", &s, &e);
			for (int j = s; j < e; j++){
				power[j]++;
			}
		}

		for (int i = 0; i < PMX; i++){
			add_edge(i + TIME, T, power[i]);
		}

		res = dinic(S, T);

		printf("Case #%d\n", test);
		if (res >= psum) printf("1\n");
		else printf("0\n");
	}

	return 0;
}
