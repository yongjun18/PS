#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct DisjointSet {
    vector<int> parent, size;
    void init(int n) {
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return;
        if (size[u] < size[v]) swap(u, v);

        parent[v] = u;
        size[u] += size[v];
    }
};

struct Edge {
    int u, v, w;
    bool operator <(const Edge &ot) const { return w < ot.w; }
};
vector<Edge> edges;
vector<Edge> mst;

void kruskal(int n) {
    DisjointSet ds;
    ds.init(n);
    sort(edges.begin(), edges.end());

    for (int i = 0; i < edges.size(); i++) {
        if (mst.size() == n - 1) break;
        Edge now = edges[i];

        if (ds.find(now.u) == ds.find(now.v)) continue;
        ds.merge(now.u, now.v);

        mst.push_back(now);
    }
}
vector<int> adj[1030];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        for(int j=i+1; j<=n; j++){
            int w;
            scanf("%d", &w);
            edges.push_back({i, j, w});
        }
    }
    kruskal(n+1);
    for(auto it : mst){
        adj[it.u].push_back(it.v);
        adj[it.v].push_back(it.u);
    }
    for(int i=1; i<=n; i++){
        sort(adj[i].begin(), adj[i].end());
        printf("%d ", adj[i].size());
        for(int nxt : adj[i]) printf("%d ", nxt);
        printf("\n");
    }
    return 0;
}
