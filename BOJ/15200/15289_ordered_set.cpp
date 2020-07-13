#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

template<class T>
using ordered_set = tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;

int n, r, k;
ll a[100100], b[100100], c[100100];
ll asum;
ll psum[100100];
ll fx[100100];
ll gx[100100];

ll sum(int x, int y){
    ll ret = psum[y];
    if(x>0) ret -= psum[x-1];
    return ret;
}
void init(){
    asum = 0;
    for(int i=0; i<n; i++){
        asum += a[i];
        b[i] -= a[i];
        c[i] -= a[i];
    }
    psum[0] = b[0];
    for(int i=1; i<n; i++)
        psum[i] = psum[i-1] + b[i];

    fx[0] = gx[0] = 0;
    for(int i=0; i<r; i++)
        fx[0] += -b[i]+c[i];
    for(int i=1; i+r-1<n; i++)
        fx[i] = fx[i-1] + (-b[i-1]) + (-b[i+r-1]+c[i+r-1]);
    for(int i=0; i<r; i++)
        gx[0] += b[i];
    for(int i=1; i+r-1<n; i++)
        gx[i] = gx[i-1] + (b[i-1]-c[i-1]) + (b[i+r-1]);
}
ll separate(ll x){
    ll cnt = 0;
    ordered_set< pair<ll,int> > oset;

    for(int i=0; i+r<=n-r; i++)
        oset.insert({sum(i, i+r-1), i});
    for(int i=n-r; i>=r; i--){
        cnt += oset.order_of_key({x-sum(i, i+r-1)+1, -1});
        oset.erase({sum(i-r, i-1), i-r});
    }
    return cnt;
}
ll overlapping(ll x){
    ll cnt = 0;
    ordered_set< pair<ll,int> > oset;

    for(int i=max(0, n-2*r+1); i<=n-r-1; i++)
        oset.insert({fx[i], i});
    for(int i=n-r; i>=1; i--){
        cnt += oset.order_of_key({x-gx[i]+1, -1});
        oset.erase({fx[i-1], i-1});
        if(r > 1 && i-r >= 0)
            oset.insert({fx[i-r], i-r});
    }
    return cnt;
}
int solve(ll x){
    ll res = separate(x) + overlapping(x);
    return (res >= k);
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
    scanf("%d %d %d", &n, &r, &k);
    for(int i=0; i<n; i++) scanf("%lld", &a[i]);
    for(int i=0; i<n; i++) scanf("%lld", &b[i]);
    for(int i=0; i<n; i++) scanf("%lld", &c[i]);
    init();

    printf("%lld\n", asum + bin_search(0, (ll)1e11));
    return 0;
}
