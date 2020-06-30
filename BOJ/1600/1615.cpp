#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9+7;
const int MOD = 1e9+7;

ll tree[10010];
ll query(int l, int r, int no, int nl, int nr) {
    if (r <= nl || nr <= l) return 0;
    if (l <= nl && nr <= r) return tree[no];
    int mid = (nl + nr) / 2;
    return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
    if (idx < nl || nr <= idx) return tree[no];
    if (nl + 1 == nr && nl == idx) return tree[no] += val;
    int mid = (nl + nr) / 2;
    return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }

vector< pair<int,int> > edge;

int main()
{
    int n, m;
    ll ans;
    scanf("%d %d", &n, &m);
    while(m--){
        int x, y;
        scanf("%d %d", &x, &y);
        edge.push_back({x, y});
    }
    sort(edge.begin(), edge.end());

    ans = 0;
    for(auto it : edge){
        int y = it.second;
        ans += query(y+1, n+1, n+1);
        update(y, 1, n+1);
    }
    printf("%lld\n", ans);
    return 0;
}
