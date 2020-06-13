#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll tree[400100];

ll query(int l, int r, int no, int nl, int nr) {
    if (r <= nl || nr <= l) return 0;
    if (l <= nl && nr <= r) return tree[no];
    int mid = (nl + nr) / 2;
    return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
    if (idx < nl || nr <= idx) return tree[no];
    if (nl + 1 == nr && nl == idx) return tree[no] = val;
    int mid = (nl + nr) / 2;
    return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }

int n;
int data[100100];
int poss[100100];

int check[100100];
int sum[100100];
int can[100100];

int solve(ll x){
    for(int i=0; i<n; i++){
        if(poss[i] > x) check[i] = 1;
        else check[i] = 0;
    }
    check[n] = 1;
    sum[0] = check[0];
    for(int i=1; i<=n; i++)
        sum[i] = sum[i-1] + check[i];
    memset(tree, 0, sizeof(tree));
    memset(can, 0, sizeof(can));
    update(n, 1, n+1);

    can[n] = 1;
    for(int i=n-1; i>=0; i--){
        int res = lower_bound(sum+i+1, sum+n+1, sum[i]+data[i])-sum;

        if(query(i+data[i], min(res+1, n+1), n+1) == 0) continue;
        update(i, 1, n+1);
        can[i] = 1;
    }
    for(int i=0; i<=n; i++){
        if(check[i] == 1 && can[i] == 0) return 0;
        if(can[i] == 1) break;
    }
    return 1;
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
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", &data[i]);
    for(int i=0; i<n; i++) scanf("%d", &poss[i]);

    printf("%lld\n", bin_search(0, 100100));
    return 0;
}
