#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Edge{ int next, w; };
vector<Edge> adj[501];
void add_edge(int u, int v, int w){
    adj[u].push_back({v, w});
}
vector<int> dist;

int bellman_ford(int n){
    dist = vector<int>(n, INF);
    int updated = 0;

    for(int t=0; t<2*n; t++){
        updated = 0;
        for(int now=0; now<n; now++){
            for(Edge e : adj[now]){
                int next = e.next;
                int w = e.w;
                if(dist[next] > dist[now] + w){
                    dist[next] = dist[now] + w;
                    updated = 1;
                }
            }
        }
        if(!updated) break;
    }
    if(updated) return 0;
    else return 1;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m, w;
        scanf("%d %d %d", &n, &m, &w);
        while(m--){
            int x, y, tt;
            scanf("%d %d %d", &x, &y, &tt);
            add_edge(x, y, tt);
            add_edge(y, x, tt);
        }
        while(w--){
            int x, y, tt;
            scanf("%d %d %d", &x, &y, &tt);
            add_edge(x, y, -tt);
        }
        if(bellman_ford(n+1) == 1) printf("NO\n");
        else printf("YES\n");

        for(int i=1; i<=n; i++) adj[i].clear();
    }
    return 0;
}
