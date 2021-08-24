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

const int MX = 2505;
const int S = 2501;
const int T = 2502;

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

int num[55][55];
char arr[55][55];
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int main()
{
	int n;
	int cnt, sum;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%s", arr[i] + 1);
	}

	cnt = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			num[i][j] = cnt++;
		}
	}

	sum = 0;
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (arr[i][j] == 'o'){
				add_edge(S, num[i][j], 1);
				sum++;
			}
			if (arr[i][j] == '.'){
				add_edge(num[i][j], T, 1);
				sum++;
			}
		}
	}

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			if (arr[i][j] == 'o'){
				for (int d = 0; d < 4; d++){
					int ni = i + dx[d];
					int nj = j + dy[d];
					if (arr[ni][nj] == '.'){
						add_edge(num[i][j], num[ni][nj], 1);
					}
				}
			}
		}
	}
	printf("%d\n", sum - dinic(S, T));
	return 0;
}
