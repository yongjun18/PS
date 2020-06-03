#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int energy[100100];
vector< pair<int,int> > adj[100100];
int parent[100100][20];
int dist[100100][20];

void dfs(int p, int now){
    for(auto it : adj[now]){
        if(it.first == p) continue;
        parent[it.first][0] = now;
        dist[it.first][0] = it.second;
        dfs(now, it.first);
    }
}
void build(int n){
    for(int j=1; j<20; j++){
        for(int i=1; i<=n; i++){
            parent[i][j] = parent[parent[i][j-1]][j-1];
            dist[i][j] = dist[i][j-1] + dist[parent[i][j-1]][j-1];
        }
    }
}
int query(int x, int eng){
    for(int i=19; i>=0; i--){
        if(eng >= dist[x][i]){
            eng -= dist[x][i];
            x = parent[x][i];
        }
    }
    return x;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", &energy[i]);

    for(int i=0; i<n-1; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    parent[1][0] = 1;
    dfs(1, 1);
    build(n);

    for(int i=1; i<=n; i++)
        printf("%d\n", query(i, energy[i]));
    return 0;
}
