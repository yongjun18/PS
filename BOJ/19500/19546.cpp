#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e12;
const int MOD = 1e9+7;

const int IN = 0;
const int OUT = 200;
const int LAYER = 400;

const int SOURCE = 2005;
const int SINK = 2006;

struct Edge {
    int from, to;
    ll capacity, flow;
    Edge* reverse;
};
vector<Edge*> adj[2010];
int level[2010];
int work[2010];

void add_edge(int u, int v, ll capacity) {
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
ll dfs(int now, int dest, ll flow) {
    if (now == dest) return flow;
    for (int &i = work[now]; i < adj[now].size(); i++) {
        Edge* e = adj[now][i];
        if (level[e->to] == level[now] + 1 && e->capacity - e->flow > 0) {
            ll amount = dfs(e->to, dest, min(e->capacity - e->flow, flow));
            if (amount > 0) {
                e->flow += amount;
                e->reverse->flow -= amount;
                return amount;
            }
        }
    }
    return 0;
}
ll dinic(int source, int sink) {
    ll total_flow = 0;
    while (bfs(source, sink)) {
        memset(work, 0, sizeof(work));
        while (1) {
            ll flow = dfs(source, sink, INF);
            if (flow == 0) break;
            total_flow += flow;
            total_flow = min((ll)INF, total_flow);
        }
    }
    return total_flow;
}
void print_ans(int n, int k, int source){
    int cnt = 0;
    vector<int> ans(n);
    vector<int> visit(2010);
    queue<int> que;

    que.push(source);
    visit[source] = 1;
    while(que.size()){
        int now = que.front(); que.pop();
        for(Edge* e : adj[now]){
            if(visit[e->to] == 0 && e->capacity-e->flow > 0){
                que.push(e->to);
                visit[e->to] = 1;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<k; j++){
            if(visit[i+IN+j*LAYER] == 1 && visit[i+OUT+j*LAYER] == 0){
                cnt++;
                ans[i] = 1;
                break;
            }
        }
    }
    printf("%d\n", cnt);
    for(int i=0; i<n; i++) if(ans[i] == 1)
        printf("%d ", i+1);
    printf("\n");
}

int cost[210];

int main()
{
    int n, m, k;
    int s, e;
    ll flow;

    scanf("%d %d %d", &n, &m, &k);
    scanf("%d %d", &s, &e);
    s--; e--;
    for(int i=0; i<n; i++) scanf("%d", &cost[i]);

    for(int i=0; i<k; i++){
        add_edge(SOURCE, s+IN+i*LAYER, INF);
        add_edge(e+OUT+i*LAYER, SINK, INF);
        for(int j=0; j<n; j++) if(i)
            add_edge(j+IN+(i-1)*LAYER, j+OUT+i*LAYER, INF);
        for(int j=0; j<n; j++)
            add_edge(j+IN+i*LAYER, j+OUT+i*LAYER, cost[j]);
    }
    while(m--){
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        for(int i=0; i<k; i++)
            add_edge(u+OUT+i*LAYER, v+IN+i*LAYER, INF);
    }
    flow = dinic(SOURCE, SINK);

    if(flow >= INF) printf("-1\n");
    else if(flow == 0) printf("0\n");
    else print_ans(n, k, SOURCE);
    return 0;
}
