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
	int n;
	ll ans;

	scanf("%d", &n);
	cow = vector< pair<int, int> >(n, { -1, -1 });
	
	for (int i = 0; i < 2 * n; i++){
		int x;
		scanf("%d", &x);
		x--;
		if (cow[x].first == -1){
			cow[x].first = i;
		}
		else{
			cow[x].second = i;
		}
	}
	sort(cow.begin(), cow.end());

	ans = 0;
	for (int i = 0; i < cow.size(); i++){
		ans += query(cow[i].first, cow[i].second);
		update(cow[i].second, 1);
	}
	printf("%lld\n", ans);
	return 0;
}
