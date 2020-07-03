#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Edge{
    int x, y;
    int need;
};
int n, m;
vector<Edge> edge;
vector<int> adj[50100];
int visit[50100];

void init(){
    for(int i=1; i<=n; i++){
        visit[i] = 0;
        adj[i].clear();
    }
    for(int i=0; i<m; i++)
        adj[edge[i].x].push_back(i);
}
void dfs(int now){
    visit[now] = 1;
    for(int e : adj[now]){
        if(visit[edge[e].y] == 0){
            edge[e].need = 1;
            dfs(edge[e].y);
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        edge.clear();
        for(int i=0; i<m; i++){
            int x, y;
            scanf("%d %d", &x, &y);
            edge.push_back({x, y, 0});
        }
        init(); dfs(1);
        for(Edge& ed : edge) swap(ed.x, ed.y);
        init(); dfs(1);
        for(Edge& ed : edge) swap(ed.x, ed.y);
    
        for(int i=0, cnt=0; cnt<m-2*n; i++){
            if(edge[i].need == 0){
                cnt++;
                printf("%d %d\n", edge[i].x, edge[i].y);
            }
        }
    }
    return 0;
}
