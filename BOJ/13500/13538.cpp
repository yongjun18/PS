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

struct PST {
	struct Node {
		Node *l, *r;
		int val;
	};

	static const int MAX_RANGE = 500100;
	static const int MAX_N = 500100;
	static const int MAX_DEPTH = 21;
	static const int MAX_NODE = MAX_RANGE * 2 + MAX_DEPTH * MAX_N;

	int cnt = 0;

	Node* root[MAX_N + 1];
	int rcnt;

	Node* build(int nl, int nr) {
		Node* now = new Node();
		if (nl + 1 < nr) {
			int mid = (nl + nr) / 2;
			now->l = build(nl, mid);
			now->r = build(mid, nr);
		}
		return now;
	}

	void init() {
		cnt = 0;
		root[0] = build(0, MAX_RANGE);
		rcnt = 1;
	}

	Node* update(int idx, int val, Node* shadow, int nl, int nr) {
		if (idx < nl || nr <= idx) return shadow;

		Node* now = new Node();
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

	int get_kth(int k, Node* pno, Node* no, int nl, int nr) {
		if (no->val - pno->val < k) return -1;
		if (nl + 1 == nr) return nl;
		int mid = (nl + nr) / 2;
		int lsum = no->l->val - pno->l->val;
		if (lsum >= k)
			return get_kth(k, pno->l, no->l, nl, mid);
		else return get_kth(k - lsum, pno->r, no->r, mid, nr);

	}
	int get_kth(int k, int s, int e) {
		return get_kth(k, root[s - 1], root[e], 0, MAX_RANGE);
	}
}pst;

struct BitTree {
	struct Node {
		vector<int> idx;
		Node *nxt0, *nxt1;
	};

	static const int MSB = 19;
	static const int MAX_N = 500100;
	static const int MAX_NODE = (MSB + 1) * MAX_N;

	int cnt = 0;
	vector<int> arr;
	Node* root;

	void init() {
		cnt = 0;
		root = new Node();
	}

	void insert(int x) {
		Node* now;
		root->idx.push_back(arr.size());
		now = root;

		for (int i = MSB; i >= 0; i--) {
			if ((1 << i) & x) {
				if (now->nxt1 == NULL) now->nxt1 = new Node();
				now = now->nxt1;
			}
			else {
				if (now->nxt0 == NULL) now->nxt0 = new Node();
				now = now->nxt0;
			}
			now->idx.push_back(arr.size());
		}
		arr.push_back(x);
	}

	void pop(int k) {
		while (k--) {
			int x = arr.back();
			Node* now;
			root->idx.pop_back();
			now = root;

			for (int i = MSB; i >= 0; i--) {
				if ((1 << i) & x) {
					now = now->nxt1;
				}
				else {
					now = now->nxt0;
				}
				now->idx.pop_back();
			}
			arr.pop_back();
		}
	}

	int sum(vector<int>& v, int l, int r) {
		return upper_bound(v.begin(), v.end(), r) - lower_bound(v.begin(), v.end(), l);
	}

	int find(int x, int l, int r) {
		int ret = 0;
		Node* now = root;

		for (int i = MSB; i >= 0; i--) {
			if (((1 << i) & x) && now->nxt1 != NULL && sum(now->nxt1->idx, l, r) > 0) {
				now = now->nxt1;
				ret += (1 << i);
			}
			else if (now->nxt0 == NULL || sum(now->nxt0->idx, l, r) == 0) {
				now = now->nxt1;
				ret += (1 << i);
			}
			else now = now->nxt0;
		}
		return ret;
	}
}bt;

int main()
{
	int m;

	scanf("%d", &m);
	pst.init();
	bt.init();

	while (m--) {
		int t;
		int l, r, k, x;
		int res;

		scanf("%d", &t);

		if (t == 1) {
			scanf("%d", &x);
			bt.insert(x);
			pst.update(x, 1);
		}
		if (t == 2) {
			scanf("%d %d %d", &l, &r, &x);
			res = bt.find(~x, l - 1, r - 1);
			printf("%d\n", res);
		}
		if (t == 3) {
			scanf("%d", &k);
			bt.pop(k);
			pst.rcnt -= k;
		}
		if (t == 4) {
			scanf("%d %d %d", &l, &r, &x);
			res = pst.query(r, 0, x + 1) - pst.query(l - 1, 0, x + 1);
			printf("%d\n", res);
		}
		if (t == 5) {
			scanf("%d %d %d", &l, &r, &k);
			printf("%d\n", pst.get_kth(k, l, r));
		}
	}

	return 0;
}
