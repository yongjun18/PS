#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int fward[1010];
vector<int> bward[1010];
int check[1010];
int depth[1010];
int dp[1010];

int last;
int minsiz, maxsiz;

int dfs2(int now){
    int ret = 1;
    for(int pv : bward[now]){
        if(check[pv] == 0){
            check[pv] = 1;
            ret += dfs2(pv);
        }
    }
    return ret;
}
void dfs(int now){
    int nxt = fward[now];
    if(depth[nxt] == -1){
        depth[nxt] = depth[now] + 1;
        dfs(nxt);
    }
    else{
        minsiz = depth[now] - depth[nxt] + 1;
        last = now;
    }
}
void update(){
    for(int i=1009; i>=0; i--){
        if(dp[i] == 0) continue;
        for(int j=minsiz; j<=maxsiz; j++)
            dp[i+j] = 1;
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++){
        scanf("%d", &fward[i]);
        bward[fward[i]].push_back(i);
    }
    memset(depth, -1, sizeof(depth));
    dp[0] = 1;
    for(int i=1; i<=n; i++){
        if(check[i] == 0){
            depth[i] = 0;
            dfs(i);

            check[last] = 1;
            maxsiz = dfs2(last);
            update();
        }
    }
    for(int i=k; i>=0; i--){
        if(dp[i] == 1){
            printf("%d\n", i);
            break;
        }
    }
    return 0;
}
