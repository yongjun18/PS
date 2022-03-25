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

struct Node {
	Node *l, *r;
	int val;
};

const int MAX_RANGE = 100100;
const int MAX_N = 10010;
const int MAX_DEPTH = 18;
const int MAX_NODE = MAX_RANGE * 2 + MAX_DEPTH * MAX_N;

int cnt = 0;
Node nodes[MAX_NODE];

Node* new_node() {
	return &nodes[cnt++];
}

Node* root[MAX_N + 1];
int rcnt;

Node* build(int nl, int nr) {
	Node* now = new_node();
	if (nl + 1 < nr) {
		int mid = (nl + nr) / 2;
		now->l = build(nl, mid);
		now->r = build(mid, nr);
	}
	return now;
}

void init() {
	for (int i = 0; i < cnt; i++)
		nodes[i] = { NULL, NULL, 0 };
	cnt = 0;
	root[0] = build(0, MAX_RANGE);
	rcnt = 1;
}

Node* update(int idx, int val, Node* shadow, int nl, int nr) {
	if (idx < nl || nr <= idx) return shadow;

	Node* now = new_node();
	if (nl + 1 == nr) now->val = shadow->val + val;
	else {
		int mid = (nl + nr) / 2;
		now->l = update(idx, val, shadow->l, nl, mid);
		now->r = update(idx, val, shadow->r, mid, nr);
		now->val = now->l->val + now->r->val;
	}
	return now;
}
void update(int idx, int val) {
	root[rcnt] = update(idx, val, root[rcnt - 1], 0, MAX_RANGE);
	rcnt++;
}

int query(int l, int r, Node* no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return no->val;
	int mid = (nl + nr) / 2;
	return query(l, r, no->l, nl, mid) + query(l, r, no->r, mid, nr);
}
int query(int k, int l, int r) { return query(l, r, root[k], 0, MAX_RANGE); }


int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int n, m;
		ll ans;
		vector< pair<int, int> > pt;

		scanf("%d %d", &n, &m);
		init();
		pt.resize(n);
		for (auto &it : pt) {
			// [y, x]
			scanf("%d %d", &it.second, &it.first);
		}
		sort(pt.begin(), pt.end());

		for (auto [y, x] : pt) {
			update(x, 1);
		}

		ans = 0;
		while (m--) {
			int l, r, b, t;
			int from, to;
			scanf("%d %d %d %d", &l, &r, &b, &t);
			from = lower_bound(pt.begin(), pt.end(), make_pair(b, -INF)) - pt.begin();
			to = upper_bound(pt.begin(), pt.end(), make_pair(t, INF)) - pt.begin();
			ans += query(to, l, r + 1) - query(from, l, r + 1);
		}
		printf("%lld\n", ans);
	}

	return 0;
}
