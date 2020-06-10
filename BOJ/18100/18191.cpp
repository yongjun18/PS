#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m, k;
ll arr[200100];

int solve(ll x){
    ll fl = 0;
    ll fr = n-1;

    for(int i=1; i<m; i++){
        ll minv, maxv;
        minv = arr[i]-x-arr[i-1];
        if(minv < 0) minv = minv/k;
        else minv = (minv+k-1)/k;

        maxv = arr[i]+x-arr[i-1];
        if(maxv < 0) maxv = (maxv-k+1)/k;
        else maxv = maxv/k;

        if(minv > maxv) return 0;
        fl = max((ll)0, fl+minv);
        fr = min((ll)n-1, fr+maxv);
        if(fl > fr) return 0;
    }
    return 1;
}
ll binary_search(ll x, ll y) {
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
    scanf("%d %d %d", &n, &m, &k);
    for(int i=0; i<m; i++)
        scanf("%lld", &arr[i]);

    printf("%lld\n", binary_search(0, 1e9));
    return 0;
}
