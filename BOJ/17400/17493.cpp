#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[200100];
int dp[200100][2][2];
int visit[200100];

void dfs(int p, int now){
    visit[now] = 1;
    for(int it : adj[now]){
        if(p == it) continue;
        dfs(now, it);
    }
    for(int it : adj[now]){
        if(p == it) continue;
        dp[now][0][0] += min(dp[it][1][0], dp[it][1][1]);
    }
    dp[now][0][1] = INF;
    dp[now][1][0] = INF;
    for(int it : adj[now]){
        if(p == it) continue;
        int tmp = dp[now][0][0] - min(dp[it][1][0], dp[it][1][1]) + dp[it][1][1];
        dp[now][1][0] = min(dp[now][1][0], tmp);
    }
    dp[now][1][1] = 1;
    for(int it : adj[now])
        dp[now][1][1] += min({dp[it][0][0], dp[it][0][1], dp[it][1][1]});
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    while(m--){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int ans = 0;
    for(int i=1; i<=n; i++){
        if(visit[i] == 0){
            dfs(i, i);
            ans += min(dp[i][1][0], dp[i][1][1]);
        }
    }
    printf("%d\n", ans);
    return 0;
}
