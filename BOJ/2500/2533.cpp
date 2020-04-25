#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[1000100];
int early[1000100];

void dfs(int p, int now){
    for(int nxt : adj[now]){
        if(p == nxt) continue;
        dfs(now, nxt);
    }
    for(int nxt : adj[now]){
        if(p == nxt) continue;
        if(early[nxt] == 0)
            early[now] = 1;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n-1; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(-1, 1);

    int ans = 0;
    for(int i=1; i<=n; i++)
        ans += early[i];
    printf("%d\n", ans);
    return 0;
}
