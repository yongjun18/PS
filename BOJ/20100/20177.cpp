#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = 1e16;
const int MOD = 1e9 + 7;

ll tree[16000100];

ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }

ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = max(tree[no], val);
	int mid = (nl + nr) / 2;
	return tree[no] = max(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }

int get_idx(int l, int r, ll val, int no, int nl, int nr){
	if (tree[no] < val) return -1;
	if (r <= nl || nr <= l) return -1;
	if (nl + 1 == nr) return nl;

	int mid = (nl + nr) / 2;
	int res2 = get_idx(l, r, val, 2 * no + 1, mid, nr);
	if (res2 != -1) return res2;
	return get_idx(l, r, val, 2 * no, nl, mid);
}
int get_idx(int l, int r, ll val, int n){ return get_idx(l, r, val, 1, 0, n); }

struct Query{
	int x, y, idx;
	ll u;
	bool operator < (const Query& rhs) const{
		return y < rhs.y;
	}
};

int arr[2010];
ll psum[2010];
vector<Query> qry;
vector<ll> ans;

vector<ll> used;
int cx(ll x){
	return lower_bound(used.begin(), used.end(), x) - used.begin();
}
int cxu(ll x){
	return upper_bound(used.begin(), used.end(), x) - used.begin();
}

int main()
{
	int n, m;
	int upd = 0;

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
	}

	for (int i = 1; i <= n; i++){
		psum[i] = psum[i - 1] + arr[i];
	}
	for (int i = 1; i <= n; i++){
		for (int j = i; j <= n; j++){
			used.push_back(psum[j] - psum[i - 1]);
		}
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	qry.resize(m);
	ans.resize(m);
	for (int i = 0; i < m; i++){
		scanf("%d %d %lld", &qry[i].x, &qry[i].y, &qry[i].u);
		qry[i].idx = i;
	}
	sort(qry.begin(), qry.end());
	
	for (int i = 0; i < m; i++){
		while (upd + 1 <= qry[i].y){
			upd++;
			for (int j = 1; j <= upd; j++){
				ll sum = psum[upd] - psum[j - 1];
				update(cx(sum), j, used.size());
			}
		}
		int idx = get_idx(0, cxu(qry[i].u), qry[i].x, used.size());
		if (idx == -1) {
			ans[qry[i].idx] = -INF;
		}
		else{
			ans[qry[i].idx] = used[idx];
		}
	}

	for (int i = 0; i < m; i++){
		if (ans[i] <= -INF) printf("NONE\n");
		else printf("%lld\n", ans[i]);
	}

	return 0;
}
