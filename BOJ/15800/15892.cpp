#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int EDGE = 302;

struct Edge {
    int from, to, capacity, flow;
    Edge* reverse;
};
vector<Edge*> adj[10500];
int level[10500];
int work[10500];

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

int ecnt = 0;
void connect(int u, int v, int c){
    int edge1 = ecnt++;
    int edge2 = ecnt++;
    add_edge(u, EDGE+edge1, INF);
    add_edge(v, EDGE+edge1, INF);
    add_edge(EDGE+edge1, EDGE+edge2, c);
    add_edge(EDGE+edge2, u, INF);
    add_edge(EDGE+edge2, v, INF);
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    while(m--){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        connect(a, b, c);
    }
    printf("%d\n", dinic(1, n));
    return 0;
}
