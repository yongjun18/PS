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
const ll INF = 1e11;
const int MOD = 1e9 + 7;

int mx;
ll tree[1000100];

void init(){
	for (int i = 0; i < 2 * mx; i++){
		tree[i] = INF;
	}
}
void update(int idx, ll val){
	for (tree[idx += mx] = val; idx > 1; idx >>= 1){
		tree[idx >> 1] = min(tree[idx], tree[idx ^ 1]);
	}
}
ll query(int l, int r){
	ll ret = INF;
	for (l += mx, r += mx; l < r; l >>= 1, r >>= 1){
		if (l & 1) ret = min(ret, tree[l++]);
		if (r & 1) ret = min(ret, tree[--r]);
	}
	return ret;
}

struct Point{
	ll x, y;
	bool operator < (const Point& rhs) const{
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
};

vector<Point> pt;
vector<ll> usex;

void compress(int n){
	usex.clear();
	for (int i = 0; i < n; i++){
		usex.push_back(pt[i].x);
	}
	sort(usex.begin(), usex.end());
	usex.erase(unique(usex.begin(), usex.end()), usex.end());

	for (int i = 0; i < n; i++){
		int pos = lower_bound(usex.begin(), usex.end(), pt[i].x) - usex.begin();
		pt[i].x = pos;
	}
}

int solve(int i, ll mid){
	int l = pt[i].x + 1;
	int r = lower_bound(usex.begin(), usex.end(), usex[pt[i].x] + mid) - usex.begin();
	ll res = query(l, r);
	if (res - pt[i].y < mid) return 0;
	return 1;
}

ll psearch(int i, ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(i, mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		ll m;
		int n;
		int nxt;
		ll ans;

		scanf("%lld %d", &m, &n);
		mx = n + 5;
		init();

		pt.clear();
		for (int i = 0; i < n; i++){
			ll x, y;
			scanf("%lld %lld", &x, &y);
			pt.push_back({ x, y });
		}
		sort(pt.begin(), pt.end());
		compress(n);

		ans = 0;
		nxt = n - 1;
		for (int i = n - 1; i >= 0; i--){
			while (pt[nxt].y != pt[i].y){
				update(pt[nxt].x, pt[nxt].y);
				nxt--;
			}
			ll res = psearch(i, 1, min(m - pt[i].y, m - usex[pt[i].x]));
			ans += res;
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
