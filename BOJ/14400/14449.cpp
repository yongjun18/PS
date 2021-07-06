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

const int MX = 100100;

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
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }

vector< pair<int, int> > cow;

int main()
{
	int n, ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int h;
		scanf("%d", &h);
		cow.push_back({ h, i });
	}
	sort(cow.begin(), cow.end());

	ans = 0;
	for (int i = n - 1; i >= 0; i--){
		ll l = query(0, cow[i].second);
		ll r = query(cow[i].second + 1, n);

		if (l > r * 2 || r > l * 2) ans++;
		update(cow[i].second, 1);
	}
	printf("%d\n", ans);
	return 0;
}
