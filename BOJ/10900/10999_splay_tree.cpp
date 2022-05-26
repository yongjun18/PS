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
	Node *par, *l, *r;
	int siz;
	ll val, lazy, sum;
};

Node *root;

// 자식 노드로부터 정보를 가져와서 갱신
void pull(Node *x) {
	// siz 값 갱신
	x->siz = 1;
	if (x->l) x->siz += x->l->siz;
	if (x->r) x->siz += x->r->siz;

	// sum 값 갱신
	x->sum = x->val;
	if (x->l) x->sum += x->l->sum;
	if (x->r) x->sum += x->r->sum;
}

// reverse 연산을 아래에 전파
void push(Node *x) {
	if (x->lazy == 0) return;

	if (x->l) {
		x->l->val += x->lazy;
		x->l->sum += x->l->siz * x->lazy;
		x->l->lazy += x->lazy;
	}
	if (x->r) {
		x->r->val += x->lazy;
		x->r->sum += x->r->siz * x->lazy;
		x->r->lazy += x->lazy;
	}
	pull(x);
	x->lazy = 0;
}

// inorder 순서를 유지하면서 x와 x->par 관계 변경
void rotate(Node *x) {
	if (x->par == NULL) return;
	Node *p = x->par;
	Node *tmp;
	if (p->l == x) {
		p->l = tmp = x->r;
		x->r = p;
	}
	else {
		p->r = tmp = x->l;
		x->l = p;
	}
	if (tmp) tmp->par = p;
	x->par = tmp = p->par;
	p->par = x;
	if (tmp == NULL) root = x;
	else if (tmp->l == p) tmp->l = x;
	else if (tmp->r == p) tmp->r = x;
	pull(p);
	pull(x);
}

// x를 root로 만들기
void splay(Node *x) {
	while (x->par) {
		Node *p = x->par;
		Node *g = p->par;
		if (g == NULL) {
			rotate(x);
		}
		else if ((g->l == p) == (p->l == x)) {
			// zig-zig
			rotate(p);
			rotate(x);
		}
		else {
			// zig-zag
			rotate(x);
			rotate(x);
		}
	}
}

// 0-based k
int get_kth(int k) {
	Node* x = root;
	if (x == NULL || x->siz <= k) return 0;
	push(x);
	while (x) {
		while (x->l && x->l->siz > k) {
			x = x->l;
			push(x);
		}
		if (x->l) k -= x->l->siz;
		if (k == 0) break;
		k--;
		x = x->r;
		push(x);
	}
	splay(x);
	return 1;
}

// root->l->r의 서브트리가 [l, r]이 됨
Node* interval(int lo, int hi) {
	Node* x;
	get_kth(hi + 1);
	x = root;
	root = root->l;
	root->par = NULL;
	get_kth(lo - 1);
	x->l = root;
	root->par = x;
	root = x;
	return root->l->r;
}

// [lo, hi] 구간을 diff 더함
void add(int lo, int hi, ll diff) {
	if (lo > hi) return;
	Node* now = interval(lo, hi);
	now->val += diff;
	now->sum += diff * now->siz;
	now->lazy += diff;
}

ll arr[1000100];

void init(int n) {
	Node* now = root = new Node();
	for (int i = 1; i <= n; i++) {
		now->r = new Node();
		now->r->par = now;
		now->r->val = arr[i];
		now = now->r;
	}
	now->r = new Node();
	now->r->par = now;
	now = now->r;

	while (1) {
		pull(now);
		if (now->par == NULL) break;
		now = now->par;
	}
}

int main()
{
	int n, m, k;

	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	init(n);

	for (int i = 0; i < m + k; i++) {
		int a, b, c;
		ll d;

		scanf("%d", &a);
		if (a == 1) {
			scanf("%d %d %lld", &b, &c, &d);
			add(b, c, d);
		}
		else {
			scanf("%d %d", &b, &c);
			printf("%lld\n", interval(b, c)->sum);
		}
	}
	return 0;
}
