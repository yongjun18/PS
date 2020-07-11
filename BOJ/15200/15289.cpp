#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 100100;
ll tree[MX*4];
ll query(int l, int r, int no, int nl, int nr) {
    if (r <= nl || nr <= l) return 0;
    if (l <= nl && nr <= r) return tree[no];
    int mid = (nl + nr) / 2;
    return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
}
ll query(int l, int r) { return query(l, r, 1, 0, MX); }
ll update(int idx, ll val, int no, int nl, int nr) {
    if (idx < nl || nr <= idx) return tree[no];
    if (nl + 1 == nr && nl == idx) return tree[no] += val;
    int mid = (nl + nr) / 2;
    return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val) { return update(idx, val, 1, 0, MX); }

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
    for(int i=0; i<n; i++) asum += a[i];
    for(int i=0; i<n; i++){
        b[i] -= a[i];
        c[i] -= a[i];
    }
    psum[0] = b[0];
    for(int i=1; i<n; i++)
        psum[i] = psum[i-1] + b[i];

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
    vector<ll> v1, v2;

    for(int i=0; i+r<=n-r; i++)
        v1.push_back(sum(i, i+r-1));
    sort(v1.begin(), v1.end());
    v2 = v1;
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    memset(tree, 0, sizeof(tree));

    for(ll it : v1){
        int pos = lower_bound(v2.begin(), v2.end(), it) - v2.begin();
        update(pos, 1);
    }
    for(int i=n-r; i>=r; i--){
        int pos = upper_bound(v2.begin(), v2.end(), x-sum(i, i+r-1)) - v2.begin();
        cnt += query(0, pos);

        pos = lower_bound(v2.begin(), v2.end(), sum(i-r, i-1)) - v2.begin();
        update(pos, -1);
    }
    return cnt;
}
ll overlapping(ll x){
    ll cnt = 0;
    vector<ll> v1, v2;

    for(int i=0; i+r<n; i++)
        v1.push_back(fx[i]);
    sort(v1.begin(), v1.end());
    v2 = v1;
    v2.erase(unique(v2.begin(), v2.end()), v2.end());
    memset(tree, 0, sizeof(tree));

    for(int i=max(0, n-2*r+1); i<=n-r-1; i++){
        int pos = lower_bound(v2.begin(), v2.end(), fx[i]) - v2.begin();
        update(pos, 1);
    }
    for(int i=n-r; i>=1; i--){
        int pos = upper_bound(v2.begin(), v2.end(), x-gx[i]) - v2.begin();
        cnt += query(0, pos);

        pos = lower_bound(v2.begin(), v2.end(), fx[i-1]) - v2.begin();
        update(pos, -1);
        if(i-r >= 0){
            pos = lower_bound(v2.begin(), v2.end(), fx[i-r]) - v2.begin();
            update(pos, 1);
        }
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

    printf("%lld\n", asum + bin_search(0, (ll)1e15));
    return 0;
}
