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
int kruskal(int n) {
    mst.clear();
    int sum = 0;
    DisjointSet ds;
    ds.init(n);
    sort(edges.begin(), edges.end());

    for (int i = 0; i < edges.size(); i++) {
        if (mst.size() == n - 1) break;
        Edge now = edges[i];

        if (ds.find(now.u) == ds.find(now.v)) continue;
        ds.merge(now.u, now.v);
        sum += now.w;
        mst.push_back(now);
    }
    return sum;
}

int main()
{
    while(1){
        int n, m, k;
        int minv, maxv;
        scanf("%d %d %d", &n, &m, &k);
        if(n == 0) break;

        edges.clear();
        for(int i=0; i<m; i++){
            char c; int x, y;
            scanf(" %c %d %d", &c, &x, &y);

            if(c == 'B') edges.push_back({x, y, 0});
            else edges.push_back({x, y, 1});
        }
        maxv = (n-1) - kruskal(n+1);

        for(int i=0; i<m; i++)
            edges[i].w ^= 1;
        minv = kruskal(n+1);

        if(minv <= k && k <= maxv) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
