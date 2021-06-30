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

const int MX = 200100;
ll tree[MX * 4];

ll build(int no, int nl, int nr){
	if (nl + 1 == nr) return tree[no] = 0;
	int mid = (nl + nr) / 2;
	return tree[no] = max(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
}
void build(int n){ build(1, 0, n); }

ll update(int idx, ll val, int no, int nl, int nr){
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr) return tree[no] = max(tree[no], val);
	int mid = (nl + nr) / 2;
	return tree[no] = max(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
void update(int idx, ll val, int n){
	update(idx, val, 1, 0, n);
}

ll query(int l, int r, int no, int nl, int nr){
	if (r <= nl || nr <= l) return -INF; 
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
ll query(int l, int r, int n){
	return query(l, r, 1, 0, n);
}

struct Range{
	int l, r;
	bool operator < (const Range& rhs) const{
		if (r != rhs.r) return r < rhs.r;
		return l > rhs.l;
	}
};
vector<Range> rg;
vector<int> used;

void compress(){
	used.clear();
	for (int i = 0; i < rg.size(); i++){
		used.push_back(rg[i].l);
		used.push_back(rg[i].r);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < rg.size(); i++){
		rg[i].l = lower_bound(used.begin(), used.end(), rg[i].l) - used.begin();
		rg[i].r = lower_bound(used.begin(), used.end(), rg[i].r) - used.begin();
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, mx;

		scanf("%d", &n);
		mx = 2 * n + 5;
		build(mx);

		rg = vector<Range>(n);
		for (int i = 0; i < n; i++){
			scanf("%d %d", &rg[i].l, &rg[i].r);
		}
		compress();
		sort(rg.begin(), rg.end());

		for (int i = 0; i < n; i++){
			ll res = query(rg[i].l, rg[i].r + 1, mx);
			update(rg[i].l, res + 1, mx);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", tree[1]);
	}

	return 0;
}
