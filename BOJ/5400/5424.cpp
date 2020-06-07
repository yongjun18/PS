#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Edge {
    int from, to;
    double capacity, flow;
    Edge* reverse;
};
const int S = 0;
const int T = 1040;
const int P = 1000;

int cnt = 0;
Edge edges[8000];
vector<Edge*> adj[1050];
int level[1050];
int work[1050];

void add_edge(int u, int v, double capacity) {
    Edge* ef = &edges[cnt++];
    Edge* er = &edges[cnt++];
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
double dfs(int now, int dest, double flow) {
    if (now == dest) return flow;
    for (int &i = work[now]; i < adj[now].size(); i++) {
        Edge* e = adj[now][i];
        if (level[e->to] == level[now] + 1 && e->capacity - e->flow > 0) {
            double amount = dfs(e->to, dest, min(e->capacity - e->flow, flow));
            if (amount > 0) {
                e->flow += amount;
                e->reverse->flow -= amount;
                return amount;
            }
        }
    }
    return 0;
}
double dinic(int source, int sink) {
    double total_flow = 0;
    while (bfs(source, sink)) {
        memset(work, 0, sizeof(work));
        while (1) {
            double flow = dfs(source, sink, INF);
            if (flow == 0) break;
            total_flow += flow;
        }
    }
    return total_flow;
}

char arr[30][32];
int k;
int num[30][30];
double init[30];

void build(int n){
    for(int i=0; i<n; i++){
        init[i] = 0;
        for(int j=0; j<n; j++){
            if(arr[i][j] == '1') init[i] += 1;
            if(arr[i][j] == 'd') init[i] += 0.5;
        }
    }
    for(int i=0; i<n; i++)
        add_edge(S, P+i, init[i]);
    k = 1;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(arr[i][j] == '.'){
                num[i][j] = k;
                add_edge(S, k, 0.5);
                add_edge(S, k+1, 0.5);
                add_edge(k, P+i, 0.5);
                add_edge(k, P+j, 0.5);
                add_edge(k+1, P+i, 0.5);
                add_edge(k+1, P+j, 0.5);
                k += 2;
            }
        }
    }
    for(int i=0; i<n; i++)
        add_edge(P+i, T, 0);
}
int can_win(int n, int x){
    int ret;
    double score = init[x];
    for(int i=0; i<n; i++){
        if(arr[x][i] == '.'){
            score += 1;
            for(Edge* it : adj[num[min(x, i)][max(x, i)]]){
                if(it->to >= P)
                    it->capacity = 0;
            }
            for(Edge* it : adj[num[min(x, i)][max(x, i)]+1]){
                if(it->to >= P)
                    it->capacity = 0;
            }
        }
    }
    for(int i=0; i<n; i++){
        if(i == x) continue;
        for(Edge* it : adj[P+i]){
            if(it->to == T)
                it->capacity = score;
        }
    }
    dinic(S, T);

    for(int i=0; i<n; i++){
        if(i == x) continue;
        for(Edge* it : adj[P+i]){
            if(it->to == T)
                it->capacity = INF;
        }
    }
    ret = (bfs(S, T) == 0);

    for(int i=0; i<cnt; i++) edges[i].flow = 0;
    for(int i=1; i<k; i++){
        for(Edge* it : adj[i]){
            if(it->to >= P)
                it->capacity = 0.5;
        }
    }
    for(int i=0; i<n; i++){
        for(Edge* it : adj[i+P]){
            if(it->to == T)
                it->capacity = 0;
        }
    }
    return ret;
}
int main()
{
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%s", arr[i]);
        build(n);

        for(int i=0; i<n; i++){
            if(can_win(n, i)) printf("%d ", i+1);
        }
        printf("\n");
        for(int i=0; i<1050; i++) adj[i].clear();
        cnt = 0;
    }
    return 0;
}
