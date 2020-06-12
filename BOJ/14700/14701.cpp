#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll tree[800400];
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
int get_kth(int k, int no, int nl, int nr) {
    if (nl + 1 == nr) return nl;
    int mid = (nl + nr) / 2;
    if (tree[2 * no] >= k) return get_kth(k, 2 * no, nl, mid);
    else return get_kth(k - tree[2 * no], 2 * no + 1, mid, nr);
}
int get_kth(int k, int n) { return get_kth(k, 1, 0, n); }

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int lmid = n/2;
    int rmid = n-lmid+1;

    int lcnt = n/2;
    int rcnt = n/2;
    int mcnt = n%2;

    for(int i=1; i<=n; i++)
        update(i, 1, n+1);

    while(m--){
        int t, a;
        scanf("%d %d", &t, &a);

        if(t==1){
            update(a, 0, n+1);
            if(lmid+2 == rmid){
                if(a <= lmid) lmid++, lcnt++;
                else rmid--, rcnt++;
                mcnt--;
            }
            if(a <= lmid) lcnt--;
            else rcnt--;
        }
        else{
            if(a <= lmid){
                if(lcnt < a) printf("0\n");
                else printf("%d\n", get_kth(a, n+1));
            }
            else if(rmid <= a){
                if(a < n+1-rcnt) printf("0\n");
                else printf("%d\n", get_kth(lcnt+mcnt+rcnt-(n-a), n+1));
            }
            else printf("%d\n", a);
        }
    }
    return 0;
}
