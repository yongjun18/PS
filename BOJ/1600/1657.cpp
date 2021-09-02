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

const int MX = 2505;
const int S = 2502;
const int T = 2503;

struct Edge{
	int from, to, capacity, flow, cost;
	Edge* rev;
};

vector<Edge*> adj[MX];

void add_edge(int u, int v, int cap, int co){
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { u, v, cap, 0, co, er };
	*er = { v, u, 0, 0, -co, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int total_flow;
int total_cost;
void MCMF(int source, int sink, int n = MX){
	total_flow = 0;
	total_cost = 0;

	while (1){
		vector<int> dist(n, INF);
		vector<int> inque(n);
		vector<Edge*> pv(n, NULL);
		queue<int> que;

		dist[source] = 0;
		que.push(source); inque[source] = 1;

		while (que.size()){
			int now = que.front(); que.pop(); inque[now] = 0;
			for (Edge* e : adj[now]){
				if (e->capacity - e->flow > 0){
					int ndist = dist[now] + e->cost;
					if (dist[e->to] > ndist){
						dist[e->to] = ndist;
						pv[e->to] = e;
						if (inque[e->to] == 0){
							que.push(e->to); inque[e->to] = 1;
						}
					}
				}
			}
		}
		if (pv[sink] == NULL) break;
		if (dist[sink] >= 0) break;

		int amount = INF;
		for (int now = sink; now != source; now = pv[now]->from)
			amount = min(amount, pv[now]->capacity - pv[now]->flow);

		total_flow += amount;
		for (int now = sink; now != source; now = pv[now]->from){
			pv[now]->flow += amount;
			pv[now]->rev->flow -= amount;
			total_cost += pv[now]->cost * amount;
		}
	}
}

int n, m;
int arr[55][55];
int num[55][55];
int price[5][5] = {
	{ 10, 8, 7, 5, 1 },
	{ 8, 6, 4, 3, 1 },
	{ 7, 4, 3, 2, 1 },
	{ 5, 3, 2, 2, 1 },
	{ 1, 1, 1, 1, 0 }
};
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int valid(int x, int y){
	return (0 <= x && x < n && 0 <= y && y < m);
}

int main()
{
	int cnt = 0;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			char c;
			scanf(" %c", &c);
			if (c == 'F') c = 'E';
			arr[i][j] = c - 'A';
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			num[i][j] = cnt++;
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if ((i + j) % 2 == 0){
				add_edge(S, num[i][j], 1, 0);
			}
			else{
				add_edge(num[i][j], T, 1, 0);
			}
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if ((i + j) % 2 == 0){
				for (int d = 0; d < 4; d++){
					int nx = i + dx[d];
					int ny = j + dy[d];
					if (valid(nx, ny)){
						add_edge(num[i][j], num[nx][ny], 1, -price[arr[i][j]][arr[nx][ny]]);
					}
				}
			}
		}
	}
	MCMF(S, T);
	printf("%d\n", -total_cost);

	return 0;
}
