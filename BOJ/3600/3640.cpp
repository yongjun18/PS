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
const int T = 2001;
const int IN = 0;
const int OUT = 1000;

const int MX = 2050;

struct Edge {
	int from, to, capacity, flow, cost;
	Edge* reverse;
};

vector<Edge*> adj[2050];

void add_edge(int u, int v, int cp, int co) {
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { u, v, cp, 0, co, er };
	*er = { v, u, 0, 0, -co, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int total_flow;
int total_cost;
int MCMF(int n, int source, int sink) {
	total_flow = 0;
	total_cost = 0;

	while (1) {
		vector<Edge*> prev(n, NULL);
		vector<int> dist(n, INF);
		vector<int> inque(n, 0);
		queue<int> q;

		q.push(source); inque[source] = 1;
		dist[source] = 0;

		while (!q.empty()) {
			int now = q.front(); q.pop(); inque[now] = 0;
			for (Edge* e : adj[now]) {
				if (e->capacity - e->flow > 0 && dist[now] + e->cost < dist[e->to]) {
					dist[e->to] = dist[now] + e->cost;
					prev[e->to] = e;

					if (!inque[e->to]) {
						q.push(e->to); inque[e->to] = 1;
					}
				}
			}
		}

		if (prev[sink] == NULL) break;

		int amount = INF;
		for (int p = sink; p != source; p = prev[p]->from)
			amount = min(amount, prev[p]->capacity - prev[p]->flow);

		for (int p = sink; p != source; p = prev[p]->from) {
			total_cost += amount * prev[p]->cost;
			prev[p]->flow += amount;
			prev[p]->reverse->flow -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}

int main()
{
	int v, e;
	
	while (scanf("%d %d", &v, &e) > 0){
		for (int i = 0; i < MX; i++){
			for (Edge *e : adj[i]) free(e);
			adj[i].clear();
		}

		add_edge(S, 1 + IN, INF, 0);
		add_edge(v + OUT, T, INF, 0);

		add_edge(1 + IN, 1 + OUT, 2, 0);
		add_edge(v + IN, v + OUT, 2, 0);

		for (int i = 2; i < v; i++){
			add_edge(i + IN, i + OUT, 1, 0);
		}

		while (e--){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u + OUT, v + IN, 1, w);
		}
		MCMF(MX, S, T);
		printf("%d\n", total_cost);
	}

	return 0;
}
