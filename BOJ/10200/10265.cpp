#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int adj[1010];
int sink[1010];
int depth[1010];
int minsiz[1010], maxsiz[1010];
int dp[1010];

void dfs(int now){
    int nxt = adj[now];
    if(sink[nxt] != 0){
        sink[now] = sink[nxt];
        maxsiz[sink[now]] += depth[now];
        return;
    }
    if(depth[nxt] != 0){
        sink[now] = now;
        minsiz[now] = depth[now]-depth[nxt]+1;
        maxsiz[now] = depth[now];
        return;
    }
    depth[nxt] = depth[now]+1;
    dfs(nxt);
    sink[now] = sink[nxt];
}

int main()
{
    int n, k, ans;
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++)
        scanf("%d", &adj[i]);

    for(int i=1; i<=n; i++){
        if(depth[i] == 0){
            depth[i] = 1;
            dfs(i);
        }
    }
    dp[0] = 1;
    for(int i=1; i<=n; i++){
        if(sink[i] != i) continue;
        for(int j=1009; j>=0; j--){
            if(dp[j] != 0){
                for(int siz=minsiz[i]; siz<=maxsiz[i]; siz++)
                    dp[j+siz] = 1;
            }
        }
    }
    ans = k;
    while(dp[ans] == 0) ans--;
    printf("%d\n", ans);
    return 0;
}
