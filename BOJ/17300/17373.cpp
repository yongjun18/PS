#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 1000100;
ll tree[MX*4];
ll update(int idx, ll val, int no, int nl, int nr) {
    if (idx < nl || nr <= idx) return tree[no];
    if (nl + 1 == nr && nl == idx) return tree[no] = val;
    int mid = (nl + nr) / 2;
    return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val){ return update(idx, val, 1, 0, MX); }
int get_kth(ll k, int no, int nl, int nr){
    if(nl+1 == nr) return nl;
    int mid = (nl+nr)/2;
    if(tree[2*no] >= k) return get_kth(k, 2*no, nl, mid);
    else return get_kth(k - tree[2*no], 2*no+1, mid, nr);
}
int get_kth(ll k){ return get_kth(k, 1, 0, MX); }


int arr[100100];
int first_app[1000100];
ll cnt[1000100];
ll psum[1000100];

struct Query{
    ll k;
    int fnum, idx;
    bool operator < (const Query& rhs) const{
        return first_app[fnum] < first_app[rhs.fnum];
    }
};
vector<Query> queries;
vector< pair<int,int> > ans;

void init(int n, int m){
    memset(first_app, -1, sizeof(first_app));
    for(int i=n-1; i>=0; i--)
        first_app[arr[i]] = i;

    for(int i=1; i<=m; i++){
        if(first_app[i] == -1)
            cnt[i] = m;
    }
    for(int i=1; i<=m; i++)
        update(i, 1);
    for(int i=n-1; i>=0; i--){
        cnt[arr[i]] = tree[1];
        update(arr[i], 0);
    }

    psum[0] = 0;
    for(int i=1; i<MX; i++)
        psum[i] = psum[i-1] + cnt[i];
}
void solve(int n, int m){
    for(int i=1; i<=m; i++)
        update(i, 1);

    int now = n-1;
    for(int i=(int)queries.size()-1; i>=0; i--){
        ll k = queries[i].k;
        int fnum = queries[i].fnum;
        int idx = queries[i].idx;
        int snum;

        if(first_app[fnum] == -1){
            snum = k-psum[fnum-1];
            ans[idx] = {fnum, snum};
            continue;
        }

        while(first_app[fnum] < now){
            update(arr[now], 0);
            now--;
        }
        snum = get_kth(k - psum[fnum-1]);
        ans[idx] = {fnum, snum};
    }
}

int main()
{
    int n, m, q;
    scanf("%d %d %d", &n, &m, &q);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    init(n, m);

    ans.resize(q);
    for(int i=0; i<q; i++){
        ll k;
        int num;
        scanf("%lld", &k);
        num = lower_bound(psum, psum+MX, k) - psum;

        if(num >= MX)
            ans[i] = {-1,-1};
        else queries.push_back({k, num, i});
    }
    sort(queries.begin(), queries.end());
    solve(n, m);

    for(int i=0; i<q; i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
