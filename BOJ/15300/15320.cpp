#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, k, x;
vector<int> adj[5010];
vector<int> cost[5010];
int siz[5010];
int dp[5010][110][110];

void dfs(int now){
    for(int nxt : adj[now])
        dfs(nxt);

    siz[now] = 1;
    for(int nxt : adj[now])
        siz[now] += siz[nxt];

    if(adj[now].size() == 0)
        dp[now][1][0] = 0;
    else if(adj[now].size() == 1){
        int s = adj[now][0];
        int scost = cost[now][0];
        for(int cons=1; cons<=k; cons++){
            for(int cut=0; cut<=(siz[s]-1)/k; cut++){
                dp[now][min(cons+1, k)][cut] =
                    min(dp[now][min(cons+1, k)][cut], dp[s][cons][cut]);
                if(cons == k)
                    dp[now][1][cut+1] =
                        min(dp[now][1][cut+1], dp[s][cons][cut] + scost);
            }
        }
    }
    else{
        int l = adj[now][0];
        int r = adj[now][1];
        int lcost = cost[now][0];
        int rcost = cost[now][1];
        for(int lcon=1; lcon<=k; lcon++){
            for(int lcut=0; lcut<=(siz[l]-1)/k; lcut++){
                for(int rcon=1; rcon<=k; rcon++){
                    for(int rcut=0; rcut<=(siz[r]-1)/k; rcut++){
                        dp[now][min(k, lcon+rcon+1)][lcut+rcut] =
                            min(dp[now][min(k, lcon+rcon+1)][lcut+rcut], dp[l][lcon][lcut] + dp[r][rcon][rcut]);
                        if(lcon == k)
                            dp[now][min(k, rcon+1)][lcut+rcut+1] =
                                min(dp[now][min(k, rcon+1)][lcut+rcut+1], dp[l][lcon][lcut] + dp[r][rcon][rcut] + lcost);
                        if(rcon == k)
                            dp[now][min(k, lcon+1)][lcut+rcut+1] =
                                min(dp[now][min(k, lcon+1)][lcut+rcut+1], dp[l][lcon][lcut] + dp[r][rcon][rcut] + rcost);
                        if(lcon == k && rcon == k)
                            dp[now][1][lcut+rcut+2] =
                                min(dp[now][1][lcut+rcut+2], dp[l][lcon][lcut] + dp[r][rcon][rcut] + lcost + rcost);
                    }
                }
            }
        }
    }
}

int main()
{
    for(int i=0; i<5010; i++){
        for(int j=0; j<110; j++){
            for(int l=0; l<110; l++)
                dp[i][j][l] = INF;
        }
    }
    scanf("%d %d %d", &n, &k, &x);
    for(int i=2; i<=n; i++){
        int p, c;
        scanf("%d %d", &p, &c);
        adj[p].push_back(i);
        cost[p].push_back(c);
    }
    dfs(1);
    if(dp[1][k][x-1] >= INF) printf("-1\n");
    else printf("%d\n", dp[1][k][x-1]);
    return 0;
}
