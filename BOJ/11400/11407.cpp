#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Edge{
	int from, to, cap, flow, cost;
	Edge* rev;
};

vector<Edge*> adj[300];
int total_flow;
int total_cost;

const int PEO = 0;
const int SHP = 100;
const int S = 205;
const int T = 206;

void add_edge(int x, int y, int cap, int co){
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { x, y, cap, 0, co, er };
	*er = { y, x, 0, 0, -co, ef };
	adj[x].push_back(ef);
	adj[y].push_back(er);
}

int MCMF(int source, int sink, int n = 210){
	total_flow = 0;
	total_cost = 0;

	while (1){
		vector<int> inque(n);
		vector<int> dist(n, INF);
		vector<Edge*> prev(n, NULL);
		queue<int> que;

		dist[source] = 0;
		que.push(source); inque[source] = 1;

		while (que.size()){
			int now = que.front();
			que.pop();
			inque[now] = 0;

			for (Edge* e : adj[now]){
				if (e->cap - e->flow <= 0) continue;

				if (dist[e->to] > dist[now] + e->cost){
					dist[e->to] = dist[now] + e->cost;
					prev[e->to] = e;

					if (inque[e->to] == 0){
						inque[e->to] = 1;
						que.push(e->to);
					}
				}
			}
		}
		if (prev[sink] == NULL) break;

		int amount = INF;
		for (int now = sink; prev[now] != NULL; now = prev[now]->from){
			amount = min(amount, prev[now]->cap - prev[now]->flow);
		}

		for (int now = sink; prev[now] != NULL; now = prev[now]->from){
			prev[now]->flow += amount;
			prev[now]->rev->flow -= amount;
			total_cost += prev[now]->cost * amount;
		}

		total_flow += amount;
	}
	return total_flow;
}

int c[110][110];
int d[110][110];

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		add_edge(S, PEO + i, x, 0);
	}
	for (int i = 0; i < m; i++){
		int x;
		scanf("%d", &x);
		add_edge(SHP + i, T, x, 0);
	}

	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			scanf("%d", &c[i][j]);
		}
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			scanf("%d", &d[i][j]);
		}
	}
	for (int i = 0; i < m; i++){
		for (int j = 0; j < n; j++){
			add_edge(PEO + j, SHP + i, c[i][j], d[i][j]);
		}
	}

	MCMF(S, T);

	printf("%d\n", total_flow);
	printf("%d\n", total_cost);
	return 0;
}
