#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e15;
const int MOD = 1e9+7;

struct Sum_Tree{
    const int MX = 1e6 + 5;
    ll sum[4000400];
    ll query(int l, int r, int no, int nl, int nr) {
        if (r <= nl || nr <= l) return 0;
        if (l <= nl && nr <= r) return sum[no];
        int mid = (nl + nr) / 2;
        return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
    }
    ll query(int l, int r) { return query(l, r, 1, 0, MX); }
    ll update(int idx, ll val, int no, int nl, int nr) {
        if (idx < nl || nr <= idx) return sum[no];
        if (nl + 1 == nr && nl == idx) return sum[no] += val;
        int mid = (nl + nr) / 2;
        return sum[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
    }
    ll update(int idx, ll val) { return update(idx, val, 1, 0, MX); }
};
struct Max_Tree{
    const int MX = 1e6 + 5;
    ll tree[4000100];
    ll lazy[4000100];
    ll build(int no, int nl, int nr){
        if(nl+1 == nr) return tree[no] = nl;
        int mid = (nl+nr)/2;
        return tree[no] = max(build(2*no, nl, mid), build(2*no+1, mid, nr));
    }
    void build(){ build(1, 0, MX); }
    void propagate(int no, int nl, int nr) {
        if (nl + 1 != nr) {
            lazy[2*no] += lazy[no];
            lazy[2*no + 1] += lazy[no];
            tree[2*no] += lazy[no];
            tree[2*no + 1] += lazy[no];
        }
        lazy[no] = 0;
    }
    void update(int l, int r, ll val, int no, int nl, int nr) {
        propagate(no, nl, nr);
        if (r <= nl || nr <= l) return;
        if (l <= nl && nr <= r) {
            lazy[no] += val;
            tree[no] += val;
            return;
        }
        int mid = (nl + nr) / 2;
        update(l, r, val, 2 * no, nl, mid);
        update(l, r, val, 2 * no + 1, mid, nr);
        tree[no] = max(tree[2*no], tree[2*no + 1]);
    }
    void update(int l, int r, ll val) { update(l, r, val, 1, 0, MX); }
    ll query(int l, int r, int no, int nl, int nr){
        propagate(no, nl, nr);
        if(r <= nl || nr <= l) return -INF;
        if(l <= nl && nr <= r) return tree[no];
        int mid = (nl + nr)/2;
        return max(query(l, r, 2*no, nl, mid), query(l, r, 2*no+1, mid, nr));
    }
    ll query(int l, int r) { return query(l, r, 1, 0, MX); }
};

Sum_Tree sumt;
Max_Tree maxt;
vector< pair<int,int> > queries;

int main()
{
    int q;
    scanf("%d", &q);

    queries.resize(q+1);
    maxt.build();
    for(int i=1; i<=q; i++){
        char c;
        scanf(" %c", &c);
        if(c == '+'){
            int t, d;
            scanf("%d %d", &t, &d);
            sumt.update(t, d);
            maxt.update(0, t+1, d);
            queries[i] = {t, d};
        }
        if(c == '-'){
            int idx, t, d;
            scanf("%d", &idx);
            t = queries[idx].first;
            d = queries[idx].second;
            sumt.update(t, -d);
            maxt.update(0, t+1, -d);
        }
        if(c == '?'){
            int idx;
            scanf("%d", &idx);
            printf("%lld\n", maxt.query(0, idx+1) - sumt.query(idx+1, sumt.MX) - idx);
        }
    }
    return 0;
}
