#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 20101;
ll sum[80808];
ll tree[80808];

void update(int l, int r, ll val, int no, int nl, int nr){
    if(r <= nl || nr <= l)
        return;
    else if(l <= nl && nr <= r)
        tree[no] += val;
    else{
        int mid = (nl+nr)/2;
        update(l, r, val, 2*no, nl, mid);
        update(l, r, val, 2*no+1, mid, nr);
    }
    if(tree[no] > 0) sum[no] = nr-nl;
    else if(nl+1 == nr) sum[no] = 0;
    else sum[no] = sum[2*no] + sum[2*no+1];
}
void update(int l, int r, ll val, int n){ update(l, r, val, 1, 0, n); }

struct Seg{
    int from, to, pos, val;
    bool operator < (const Seg& rhs) const{
        if(pos != rhs.pos) return pos < rhs.pos;
        return val > rhs.val;
    }
};
ll compute(vector<Seg>& v){
    ll ret = 0;
    sort(v.begin(), v.end());
    for(Seg it : v){
        ll pv = sum[1];
        update(it.from, it.to, it.val, MX);
        ret += abs(sum[1] - pv);
    }
    return ret;
}
int cx1[5010], cy1[5010];
int cx2[5010], cy2[5010];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d", &cx1[i], &cy1[i], &cx2[i], &cy2[i]);
        if(cx1[i] > cx2[i]) swap(cx1[i], cx2[i]);
        if(cy1[i] > cy2[i]) swap(cy1[i], cy2[i]);
        cx1[i] += 10000; cy1[i] += 10000;
        cx2[i] += 10000; cy2[i] += 10000;
    }

    ll ans = 0;
    vector<Seg> v;
    for(int i=0; i<n; i++){
        v.push_back({cy1[i], cy2[i], cx1[i], 1});
        v.push_back({cy1[i], cy2[i], cx2[i], -1});
    }
    ans += compute(v);
    v.clear();
    for(int i=0; i<n; i++){
        v.push_back({cx1[i], cx2[i], cy1[i], 1});
        v.push_back({cx1[i], cx2[i], cy2[i], -1});
    }
    ans += compute(v);
    printf("%lld\n", ans);
    return 0;
}
