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

const int MX = 1000100;

struct Seg {
	ll arr[MX];
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

int p[MX];
int q[MX];

Seg seg[3];
vector< pair<int, int> > vec;
ll cnt[3][MX];

int main()
{
	int n;
	int nxt;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &q[i]);
	}
	for (int i = 0; i < n; i++) {
		vec.push_back({ p[i], q[i] });
	}
	sort(vec.begin(), vec.end());

	nxt = 0;
	for (int idx = 0; idx < n; idx++) {
		while (vec[nxt].first < vec[idx].first) {
			int nqv = vec[nxt].second;
			seg[0].update(nqv, cnt[0][nxt]);
			seg[1].update(nqv, cnt[1][nxt]);
			seg[2].update(nqv, cnt[2][nxt]);
			nxt++;
		}
		int qv = vec[idx].second;
		cnt[0][idx] = 1;
		cnt[1][idx] = seg[0].query(0, qv);
		cnt[2][idx] = seg[1].query(0, qv);
	}
	while (nxt < n) {
		int nqv = vec[nxt].second;
		seg[0].update(nqv, cnt[0][nxt]);
		seg[1].update(nqv, cnt[1][nxt]);
		seg[2].update(nqv, cnt[2][nxt]);
		nxt++;
	}
	printf("%lld\n", seg[2].tree[1]);
	return 0;
}
