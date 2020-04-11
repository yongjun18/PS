#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int MOD = 1e9+7;

int n, m, r, s;
int arr[20][20];
int cut[20];
int group[20];
ll sum[20];

void grouping(){
    group[0] = 0;
    for(int i=1; i<m; i++){
        if(cut[i-1])
            group[i] = group[i-1]+1;
        else group[i] = group[i-1];
    }
}
int solve(ll x){
    int now = 0;
    int cut_count = 0;
    memset(sum, 0, sizeof(sum));

    while(1){
        if(cut_count > r) return 0;
        if(now > n) break;

        int ok = 1;
        for(int i=0; i<m; i++){
            sum[group[i]] += arr[now][i];
            if(sum[group[i]] > x) ok = 0;
        }
        if(ok) now++;
        else{
            cut_count++;
            memset(sum, 0, sizeof(sum));
        }
    }
    return 1;
}
ll binary_search(ll x, ll y) {
    ll lo = x-1;
    ll hi = y+1;
    grouping();
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
ll dfs(int now, int cut_count){
    if(now >= m-1){
        if(cut_count == s)
            return binary_search(0, 2000000LL * 18 * 18);
        else return INF;
    }
    cut[now] = 0;
    ll res1 = dfs(now+1, cut_count);

    cut[now] = 1;
    ll res2 = dfs(now+1, cut_count+1);
    return min(res1, res2);
}
int main()
{
    scanf("%d %d %d %d", &n, &m, &r, &s);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            scanf("%d", &arr[i][j]);
    }
    printf("%lld\n", dfs(0, 0));
    return 0;
}
