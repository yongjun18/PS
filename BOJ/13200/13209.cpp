#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, k;
int people[100100];
vector<int> adj[100100];
int pv[100100];

vector<int> height[100100];
ll sum[100100];

void dfs(int now, int h){
    for(int nxt : adj[now]){
        if(nxt == pv[now]) continue;
        pv[nxt] = now;
        height[h+1].push_back(nxt);
        dfs(nxt, h+1);
    }
}
int solve(ll x){
    int cnt = 0;

    for(int i=n; i>=0; i--){
        for(int now : height[i]){
            if(people[now] > x) return 0;
            vector<ll> v;
            for(int nxt : adj[now]){
                if(nxt == pv[now]) continue;
                v.push_back(sum[nxt]);
            }
            sort(v.begin(), v.end());

            sum[now] = people[now];
            for(ll it : v){
                if(sum[now] + it > x) cnt++;
                else sum[now] += it;
            }
        }
    }
    return (cnt <= k);
}
ll bin_search(ll x, ll y) {
    ll lo = x - 1;
    ll hi = y + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &k);
        for(int i=1; i<=n; i++)
            scanf("%d", &people[i]);
        for(int i=0; i<n-1; i++){
            int x, y;
            scanf("%d %d", &x, &y);
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        pv[1] = 1;
        height[0].push_back(1);
        dfs(1, 0);

        printf("%lld\n", bin_search(1, 1e15));

        for(int i=0; i<=n; i++){
            adj[i].clear();
            height[i].clear();
        }
    }
    return 0;
}
