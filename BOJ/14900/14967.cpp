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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

const int MX = 200100;
ll tree[4 * MX];

ll build(int no, int nl, int nr) {
	if (nl + 1 == nr) return tree[no] = INF;
	int mid = (nl + nr) / 2;
	return tree[no] = min(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
}
ll build(int n = MX) { return build(1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = min(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }
int query(int l, int r, ll x, int no, int nl, int nr){
	if (r <= nl || nr <= l) return -1;
	if (tree[no] > x) return -1;
	if (nl + 1 == nr) return nl;

	int mid = (nl + nr) / 2;
	int resl = query(l, r, x, 2 * no, nl, mid);
	if (resl != -1) return resl;
	return query(l, r, x, 2 * no + 1, mid, nr);
}
int query(int l, int r, ll x, int n = MX){ return query(l, r, x, 1, 0, n); }

int main()
{
	int n, q;

	scanf("%d %d", &n, &q);
	build();

	while (q--){
		char t;
		scanf(" %c", &t);
		if (t == 'M'){
			int x, a;
			scanf("%d %d", &x, &a);
			update(a, x);
		}
		else{
			int y, b;
			scanf("%d %d", &y, &b);
			printf("%d\n", query(b, MX, y));
		}
	}

	return 0;
}
