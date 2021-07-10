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

const int MX = 300100;

struct Seg{
	ll tree[4 * MX];
	ll query(int l, int r, int no, int nl, int nr) {
		if (r <= nl || nr <= l) return 0;
		if (l <= nl && nr <= r) return tree[no];
		int mid = (nl + nr) / 2;
		return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
	}
	ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
	ll update(int idx, ll val, int no, int nl, int nr) {
		if (idx < nl || nr <= idx) return tree[no];
		if (nl + 1 == nr && nl == idx) return tree[no] += val;
		int mid = (nl + nr) / 2;
		return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
	}
	ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }
};

Seg oseg, eseg;

int main()
{
	int n, q;

	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++){
		int c;
		scanf("%d", &c);
		if (i % 2 == 1) oseg.update(i, c);
		else eseg.update(i, c);
	}

	while (q--){
		int t, l, r, x;
		scanf("%d", &t);
		if (t == 1){
			scanf("%d %d", &l, &r);
			ll res = abs(oseg.query(l, r + 1) - eseg.query(l, r + 1));
			printf("%lld\n", res);
		}
		else{
			scanf("%d %d", &l, &x);
			if (l % 2 == 1) oseg.update(l, x);
			else eseg.update(l, x);
		}
	}

	return 0;
}
