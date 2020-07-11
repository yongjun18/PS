#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, k, x;
struct Edge{ int to, w; };
vector<Edge> adj[5010];

int siz[5010];
int dp[5010][105][105];

int g(int gnum){ return min(gnum, x); }
int c(int cnt){ return min(cnt, k); }
void upd(int &to, int val){ to = min(to, val); }

void dfs(int now){
    siz[now] = 1;
    for(Edge it : adj[now]){
        dfs(it.to);
        siz[now] += siz[it.to];
    }

    if(adj[now].size() == 0)
        dp[now][0][1] = 0;

    if(adj[now].size() == 1){
        int l = adj[now][0].to;
        int lw = adj[now][0].w;
        for(int lgnum=0; lgnum<=g(siz[l]/k); lgnum++){
            for(int lcnt=0; lcnt<=k; lcnt++){
                int lpain = dp[l][lgnum][lcnt];
                if(lpain >= INF) continue;

                upd(dp[now][lgnum][c(lcnt+1)], lpain);
                if(lcnt >= k)
                    upd(dp[now][g(lgnum+1)][1], lpain + lw);
            }
        }
    }

    if(adj[now].size() == 2){
        int l = adj[now][0].to;
        int lw = adj[now][0].w;
        int r = adj[now][1].to;
        int rw = adj[now][1].w;
        for(int lgnum=0; lgnum<=g(siz[l]/k); lgnum++){
            for(int lcnt=0; lcnt<=k; lcnt++){
                for(int rgnum=0; rgnum<=g(siz[r]/k); rgnum++){
                    for(int rcnt=0; rcnt<=k; rcnt++){
                        int lpain = dp[l][lgnum][lcnt];
                        int rpain = dp[r][rgnum][rcnt];
                        if(lpain >= INF || rpain >= INF) continue;

                        upd(dp[now][g(lgnum+rgnum)][c(lcnt+rcnt+1)], lpain+rpain);
                        if(lcnt >= k)
                            upd(dp[now][g(lgnum+rgnum+1)][c(rcnt+1)], lpain+rpain+lw);
                        if(rcnt >= k)
                            upd(dp[now][g(lgnum+rgnum+1)][c(lcnt+1)], lpain+rpain+rw);
                        if(lcnt >= k && rcnt >= k)
                            upd(dp[now][g(lgnum+rgnum+2)][1], lpain+rpain+rw+lw);
                    }
                }
            }
        }
    }
}

int main()
{
    int ans;
    scanf("%d %d %d", &n, &k, &x);
    for(int i=2; i<=n; i++){
        int p, w;
        scanf("%d %d", &p, &w);
        adj[p].push_back({i, w});
    }
    for(int i=1; i<=n; i++){
        for(int j=0; j<=x; j++){
            for(int l=0; l<=k; l++)
                dp[i][j][l] = INF;
        }
    }
    dfs(1);

    ans = dp[1][x-1][k];
    for(int cnt=0; cnt<=k; cnt++)
        upd(ans, dp[1][x][cnt]);

    if(ans >= INF) printf("-1\n");
    else printf("%d\n", ans);
    return 0;
}
