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

const int MX = 500100;

struct MaxSeg{
	ll tree[4 * MX];
	ll query(int l, int r, int no, int nl, int nr) {
		if (r <= nl || nr <= l) return -INF;
		if (l <= nl && nr <= r) return tree[no];
		int mid = (nl + nr) / 2;
		return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
	}
	ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
	ll update(int idx, ll val, int no, int nl, int nr) {
		if (idx < nl || nr <= idx) return tree[no];
		if (nl + 1 == nr && nl == idx) return tree[no] = val;
		int mid = (nl + nr) / 2;
		return tree[no] = max(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
	}
	ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }
};
struct MinSeg{
	ll tree[4 * MX];
	ll query(int l, int r, int no, int nl, int nr) {
		if (r <= nl || nr <= l) return INF;
		if (l <= nl && nr <= r) return tree[no];
		int mid = (nl + nr) / 2;
		return min(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
	}
	ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
	ll update(int idx, ll val, int no, int nl, int nr) {
		if (idx < nl || nr <= idx) return tree[no];
		if (nl + 1 == nr && nl == idx) return tree[no] = val;
		int mid = (nl + nr) / 2;
		return tree[no] = min(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
	}
	ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }
};

struct Domino{
	ll x, h;
	Domino(ll _x, ll _h){ x = _x; h = _h; }
	bool operator < (const Domino& rhs) const{
		return x < rhs.x;
	}
};

vector<Domino> dmn;
MinSeg segl;
MaxSeg segr;
int l[MX];
int r[MX];
int dp[MX];

int main()
{
	int n;

	scanf("%d", &n);
	dmn.push_back({ -(ll)1e15, -(ll)1e15 });
	for (int i = 1; i <= n; i++){
		ll x, h;
		scanf("%lld %lld", &x, &h);
		dmn.push_back({ x, h });
	}
	sort(dmn.begin(), dmn.end());

	for (int i = 1; i <= n; i++){
		int pl = lower_bound(dmn.begin(), dmn.end(), Domino(dmn[i].x - dmn[i].h, 0)) - dmn.begin();
		l[i] = min(pl, (int)segl.query(pl, i));
		segl.update(i, l[i]);
	}
	for (int i = n; i >= 1; i--){
		int pr = upper_bound(dmn.begin(), dmn.end(), Domino(dmn[i].x + dmn[i].h, 0)) - dmn.begin() - 1;
		r[i] = max(pr, (int)segr.query(i + 1, pr + 1));
		segr.update(i, r[i]);
	}

	dp[0] = 0;
	for (int i = 1; i <= n; i++){
		dp[i] = n;
	}
	for (int i = 1; i <= n; i++){
		dp[i] = min(dp[i], dp[l[i] - 1] + 1);
		dp[r[i]] = min(dp[r[i]], dp[i - 1] + 1);
	}
	printf("%d\n", dp[n]);
	return 0;
}
