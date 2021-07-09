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

pair<int, int> tree[4 * MX];

pair<int, int> build(int no, int nl, int nr) {
	if (nl + 1 == nr) return tree[no] = { INF, INF };
	int mid = (nl + nr) / 2;
	return tree[no] = min(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
}
pair<int, int> build(int n = MX) { return build(1, 0, n); }
pair<int, int> update(int idx, pair<int, int> val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = min(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
pair<int, int> update(int idx, pair<int, int> val, int n = MX) { return update(idx, val, 1, 0, n); }
int query(int no, int nl, int nr) {
	if (nl + 1 == nr) return nl;
	int mid = (nl + nr) / 2;
	if (tree[2 * no] < tree[2 * no + 1]) return query(2 * no, nl, mid);
	else return query(2 * no + 1, mid, nr);
}
int query(int n = MX) { return query(1, 0, n); }

int r[MX], g[MX], b[MX];
int id[MX];

set< pair<int, int> > rset, gset, bset;
vector<int> updc;

int get_uniq(set< pair<int, int> > &st, int val, int i){
	auto it = st.find(make_pair(val, i));
	pair<int, int> pv, nxt;

	if (it == st.begin()) pv = *(st.rbegin());
	else pv = *(prev(it));

	if (next(it) == st.end()) nxt = *(st.begin());
	else nxt = *(next(it));

	if (pv.first == val || nxt.first == val)
		return 0;
	else{
		int la = (val + 360 - pv.first) % 360;
		int ra = (nxt.first + 360 - val) % 360;
		return la + ra;
	}
}

int get_uniq(int i){
	int resr = get_uniq(rset, r[i], i);
	int resg = get_uniq(gset, g[i], i);
	int resb = get_uniq(bset, b[i], i);
	return resr + resg + resb;
}

void remov(set< pair<int, int> > &st, int val, int i){
	auto it = st.find(make_pair(val, i));

	if (it == st.begin()) updc.push_back(st.rbegin()->second);
	else updc.push_back(prev(it)->second);

	if (next(it) == st.end()) updc.push_back(st.begin()->second);
	else updc.push_back(next(it)->second);

	st.erase(it);
}

void remov(int i){
	updc.clear();
	remov(rset, r[i], i);
	remov(gset, g[i], i);
	remov(bset, b[i], i);
	update(i, make_pair(INF, INF));
	for (int it : updc){
		update(it, make_pair(get_uniq(it), -id[it]));
	}
}

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d %d %d %d", &r[i], &g[i], &b[i], &id[i]);
		rset.insert(make_pair(r[i], i));
		gset.insert(make_pair(g[i], i));
		bset.insert(make_pair(b[i], i));
	}

	build();
	for (int i = 1; i <= n; i++){
		update(i, make_pair(get_uniq(i), -id[i]));
	}

	for (int i = 1; i <= n; i++){
		int idx = query();
		printf("%d\n", id[idx]);
		if (i < n) remov(idx);
	}

	return 0;
}
