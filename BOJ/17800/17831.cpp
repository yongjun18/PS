#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[200100];
vector<int> adj[200100];
ll dp[200100][2];

void dfs(int now){
    for(int it : adj[now])
        dfs(it);
    for(int it : adj[now])
        dp[now][0] += max(dp[it][0], dp[it][1]);
    for(int it : adj[now]){
        ll tmp = dp[now][0] - max(dp[it][0], dp[it][1]) + dp[it][0] + arr[now]*arr[it];
        dp[now][1] = max(dp[now][1], tmp);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for(int i=2; i<=n; i++){
        int p;
        scanf("%d", &p);
        adj[p].push_back(i);
    }
    for(int i=1; i<=n; i++)
        scanf("%d", &arr[i]);
    dfs(1);
    printf("%lld\n", max(dp[1][0], dp[1][1]));
    return 0;
}
