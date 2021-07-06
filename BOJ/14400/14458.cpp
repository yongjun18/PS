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

int n;
int arrl[MX];
int arrr[MX];

ll intl[MX];
ll intr[MX];
vector< pair<int, int> > cow;

ll solve(){
	ll now, ans;
	memset(tree, 0, sizeof(tree));
	cow = vector< pair<int, int> >(n);

	for (int i = 1; i <= n; i++){
		cow[arrl[i] - 1].second = i;
	}
	for (int i = 1; i <= n; i++){
		cow[arrr[i] - 1].first = i;
	}
	sort(cow.begin(), cow.end());

	for (int i = 0; i < cow.size(); i++){
		intl[cow[i].first] = query(cow[i].second + 1, MX);
		update(cow[i].second, 1);
	}
	memset(tree, 0, sizeof(tree));
	for (int i = (int)cow.size() - 1; i >= 0; i--){
		intr[cow[i].first] = query(0, cow[i].second);
		update(cow[i].second, 1);
	}

	now = 0;
	for (int i = 1; i <= n; i++){
		now += intl[i];
	}
	ans = now;

	for (int i = n; i >= 2; i--){
		now -= intl[i] - (i - 1 - intl[i]);
		now += intr[i] - (n - i - intr[i]);
		ans = min(ans, now);
	}
	return ans;
}

int main()
{
	ll res1, res2;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &arrl[i]);
	}
	for (int i = 1; i <= n; i++){
		scanf("%d", &arrr[i]);
	}

	res1 = solve();
	for (int i = 1; i <= n; i++){
		swap(arrl[i], arrr[i]);
	}
	res2 = solve();
	printf("%lld\n", min(res1, res2));
	return 0;
}
