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
const int MAX_N = 100100;
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

int arr[100100];
vector<int> used;

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		used.push_back(arr[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	init();
	for (int i = 0; i < n; i++) {
		int pos = lower_bound(used.begin(), used.end(), arr[i]) - used.begin();
		update(pos, 1);
	}

	while (m--) {
		int l, r, k;
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", used[get_kth(k, l, r)]);
	}

	return 0;
}
