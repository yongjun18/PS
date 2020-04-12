#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18;
const int MOD = 1e9+7;

int n;
int arr[101010];

int solve(ll x){
    int cnt1 = 0;
    ll need1 = 0;
    for(int i=0; i<n; i++){
        if(arr[i] <= x) cnt1++;
        else need1 += (arr[i]+x-1)/x - 2;
    }
    if(cnt1 != n) need1++;
    return need1 <= cnt1;
}
ll binary_search(ll x, ll y) {
    ll lo = x-1;
    ll hi = y+1;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/ 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    printf("%lld\n", binary_search(1, (ll)1e9));
    return 0;
}
