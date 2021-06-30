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

const int MX = 15000;

struct Edge{
	int from, to, cap, flow;
	Edge* rev;
};

int ecnt;
Edge edges[600100];

int cnt;
vector<Edge*> adj[MX];
int level[MX];
int work[MX];

void init(){
	for (int i = 0; i < cnt; i++){
		adj[i].clear();
	}
	ecnt = 0;
	cnt = 0;
}

int new_node(){
	return cnt++;
}
Edge* new_edge(){
	return &edges[ecnt++];
}
void add_edge(int u, int v, int cap){
	Edge* ef = new_edge();
	Edge* er = new_edge();
	*ef = { u, v, cap, 0, er };
	*er = { v, u, 0, 0, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

int bfs(int source, int sink){
	queue<int> que;
	for (int i = 0; i < cnt; i++) level[i] = -1;
	level[source] = 0;
	que.push(source);

	while (que.size()){
		int now = que.front();
		que.pop();
		for (Edge *e : adj[now]){
			if (level[e->to] == -1 && e->cap - e->flow > 0){
				level[e->to] = level[now] + 1;
				que.push(e->to);
			}
		}
	}
	return level[sink] != -1;
}

int dfs(int now, int dest, int amount){
	if (now == dest) return amount;

	for (int &i = work[now]; i < adj[now].size(); i++){
		Edge *e = adj[now][i];
		if (level[e->to] == level[now] + 1 && e->cap - e->flow > 0){
			int minv = min(amount, e->cap - e->flow);
			int res = dfs(e->to, dest, minv);
			if (res > 0){
				e->flow += res;
				e->rev->flow -= res;
				return res;
			}
		}
	}
	return 0;
}

int dinic(int source, int sink){
	int total_flow = 0;

	while (bfs(source, sink)){
		for (int i = 0; i < cnt; i++) work[i] = 0;
		while (1){
			int res = dfs(source, sink, INF);
			if (res == 0) break;
			total_flow += res;
		}
	}
	return total_flow;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		printf("Case #%d\n", test);

		int n, p, m;
		int ok;
		int fsum;
		int res;

		int source;
		int sink;
		vector<int> team;
		vector< vector<int> > week;
		vector< vector<int> > area;

		init();

		scanf("%d %d %d", &n, &p, &m);

		source = new_node();
		sink = new_node();
		team = vector<int>(n + 5);
		for (int i = 1; i <= n; i++) team[i] = new_node();
		week = vector< vector<int> >(n + 5, vector<int>(p + 5));
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= p; j++){
				week[i][j] = new_node();
			}
		}
		area = vector< vector<int> >(p + 5, vector<int>(n + 5));
		for (int i = 1; i <= p; i++){
			for (int j = 1; j <= n; j++){
				area[i][j] = new_node();
			}
		}

		for (int i = 1; i <= n; i++){
			add_edge(source, team[i], m);
		}
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= p; j++){
				add_edge(team[i], week[i][j], 1);
			}
		}

		fsum = 0;
		ok = 1;
		for (int i = 1; i <= p; i++){
			int f;
			scanf("%d", &f);
			if (f > n){
				ok = 0;
				break;
			}
			fsum += f;
			for (int j = 1; j <= f; j++){
				add_edge(area[i][j], sink, 1);
			}
		}
		if (ok == 0){
			printf("0\n");
			continue;
		}

		for (int i = 1; i <= n; i++){
			int h;
			scanf("%d", &h);
			while (h--){
				int j, k;
				scanf("%d %d", &j, &k);
				add_edge(week[i][j], area[j][k], 1);
			}
		}

		res = dinic(source, sink);
		if (res >= fsum){
			printf("1\n");
		}
		else{
			printf("0\n");
		}

	}

	return 0;
}
