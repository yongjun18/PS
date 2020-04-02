#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll tree[404040];
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
int get_kth(int k, int no, int nl, int nr){
    if(nl+1 == nr) return nl;
    int mid = (nl+nr)/2;
    if(tree[2*no] >= k) return get_kth(k, 2*no, nl, mid);
    else return get_kth(k-tree[2*no], 2*no+1, mid, nr);
}
int get_kth(int k, int n){ return get_kth(k, 1, 0, n); }

int ans[101010];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        update(i, 1, n);

    for(int i=1; i<=n; i++){
        int x;
        scanf("%d", &x);
        int pos = get_kth(x+1, n);
        ans[pos] = i;
        update(pos, 0, n);
    }
    for(int i=0; i<n; i++)
        printf("%d\n", ans[i]);
    return 0;
}
