#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Seg{
	int mx;
	vector<ll> tree;

	void init(int n){
		mx = n;
		tree = vector<ll>(2 * n);
	}
	void update(int idx, ll val) {
		for (tree[idx += mx] = val; idx > 1; idx >>= 1)
			tree[idx >> 1] = tree[idx] + tree[idx ^ 1];
	}
	ll query(int l, int r) {
		ll res = 0;
		for (l += mx, r += mx; l < r; l >>= 1, r >>= 1){
			if (l & 1) res += tree[l++];
			if (r & 1) res += tree[--r];
		}
		return res;
	}
};

const int MX = 100100;
vector<int> tree[4 * MX];
Seg seg[4 * MX];

int l[MX], r[MX];
int li[MX], ri[MX];
int nxt[MX];

void build(int no, int nl, int nr){
	if (nl + 1 == nr){
		tree[no].push_back(r[nl]);
		seg[no].init(1);
		return;
	}
	int mid = (nl + nr) / 2;
	build(2 * no, nl, mid);
	build(2 * no + 1, mid, nr);

	vector<int> &l = tree[2 * no];
	vector<int> &r = tree[2 * no + 1];
	tree[no].resize(l.size() + r.size());
	merge(l.begin(), l.end(), r.begin(), r.end(), tree[no].begin());
	seg[no].init(tree[no].size());
}
void build(int n = MX){ build(1, 0, n); }

void update(int idx, int val, int no, int nl, int nr){
	if (idx < nl || nr <= idx) return;

	int pos = lower_bound(tree[no].begin(), tree[no].end(), val) - tree[no].begin();
	seg[no].update(pos, 1);

	if (nl + 1 == nr) return;
	int mid = (nl + nr) / 2;
	update(idx, val, 2 * no, nl, mid);
	update(idx, val, 2 * no + 1, mid, nr);
}
void update(int idx, int val, int n = MX){ update(idx, val, 1, 0, n); }

int query(int l, int r, int k, int greater, int no, int nl, int nr){
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r){
		if (greater){
			int pos = upper_bound(tree[no].begin(), tree[no].end(), k) - tree[no].begin();
			return seg[no].query(pos, seg[no].mx);
		}
		else{
			int pos = lower_bound(tree[no].begin(), tree[no].end(), k) - tree[no].begin();
			return seg[no].query(0, pos);
		}
	}
	int mid = (nl + nr) / 2;
	return query(l, r, k, greater, 2 * no, nl, mid) + query(l, r, k, greater, 2 * no + 1, mid, nr);
}
int query(int l, int r, int k, int greater, int n = MX){ return query(l, r, k, greater, 1, 0, n); }

int main()
{
	int n, k;
	ll ans;

	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++){
		scanf("%d", &l[i]);
		li[l[i]] = i;
	}
	for (int i = 0; i < n; i++){
		scanf("%d", &r[i]);
		ri[r[i]] = i;
	}
	for (int i = 1; i <= n; i++){
		nxt[li[i]] = ri[i];
	}

	build();

	ans = 0;
	for (int i = 0; i < n; i++){
		ans += query(nxt[i] + 1, MX, l[i] + k, 1);
		ans += query(nxt[i] + 1, MX, l[i] - k, 0);
		update(nxt[i], l[i]);
	}
	printf("%lld\n", ans);

	return 0;
}
