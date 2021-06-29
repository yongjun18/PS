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

const int HOR = 0;
const int VER = 400;
const int IN = 0;
const int OUT = 200;
const int S = 0;
const int T = 801;

const int MX = 810;

struct Edge {
	int from, to, capacity, flow, cost;
	Edge* reverse;
};
vector<Edge*> adj[810];

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

struct Line{
	int x1, y1, x2, y2, w;
};
vector<Line> ver, hor;

int inters(Line h, Line v){
	if (h.x1 > h.x2) swap(h.x1, h.x2);
	if (v.y1 > v.y2) swap(v.y1, v.y2);

	return h.x1 < v.x1 && v.x1 < h.x2 &&
		v.y1 < h.y1 && h.y1 < v.y2;
}

int main()
{
	int t;

	scanf("%d", &t);

	while (t--){
		int n, m;

		for (int i = 0; i < MX; i++){
			for (Edge* e : adj[i]) free(e);
			adj[i].clear();
		}
		ver.clear(); 
		ver.resize(1);
		hor.clear(); 
		hor.resize(1);

		scanf("%d %d", &n, &m);
		
		for (int i = 0; i < n; i++){
			int x1, y1, x2, y2, w;
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
			hor.push_back({ x1, y1, x2, y2, w });
		}
		for (int i = 0; i < m; i++){
			int x1, y1, x2, y2, w;
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
			ver.push_back({ x1, y1, x2, y2, w });
		}

		for (int i = 1; i <= n; i++){
			add_edge(S, i + HOR + IN, INF, 0);
			add_edge(i + HOR + IN, i + HOR + OUT, 1, 0);
		}
		for (int i = 1; i <= m; i++){
			add_edge(i + VER + IN, i + VER + OUT, 1, 0);
			add_edge(i + VER + OUT, T, INF, 0);
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= m; j++){
				if (inters(hor[i], ver[j])){
					add_edge(i + HOR + OUT, j + VER + IN, INF, -hor[i].w * ver[j].w);
				}
			}
		}
		MCMF(MX, S, T);
		printf("%d %d\n", total_flow, -total_cost);
	}

	return 0;
}
