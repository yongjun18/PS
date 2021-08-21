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

const int MX = 305;
const int S = 0;
const int T = 302;
const int FAMILY = 0;
const int HOUSE = 150;

struct Edge {
	int from, to, capacity, flow, cost;
	Edge* reverse;
};
vector<Edge*> adj[MX];

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
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		add_edge(u + FAMILY, v + HOUSE, 1, -w);
	}

	for (int i = 1; i <= n; i++){
		add_edge(S, i + FAMILY, 1, 0);
		add_edge(i + FAMILY, i + HOUSE, 1, 0);
		add_edge(i + HOUSE, T, 1, 0);
	}

	MCMF(MX, S, T);
	printf("%.9lf\n", -(double)total_cost / 20);

	return 0;
}
