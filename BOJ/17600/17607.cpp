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
	int rev;
	int val, longest, l1, r1;
};

Node *root;

// 자식 노드로부터 정보를 가져와서 갱신
void pull(Node *x) {
	// siz 값 갱신
	x->siz = 1;
	if (x->l) x->siz += x->l->siz;
	if (x->r) x->siz += x->r->siz;

	// l1 값 갱신
	if (x->l) x->l1 = x->l->l1;
	else x->l1 = 0;
	if (x->l == NULL || x->l->siz == x->l->l1) {
		if (x->val == 1) {
			x->l1 += 1;
			if (x->r) x->l1 += x->r->l1;
		}
	}

	// r1 값 갱신
	if (x->r) x->r1 = x->r->r1;
	else x->r1 = 0;
	if (x->r == NULL || x->r->siz == x->r->r1) {
		if (x->val == 1) {
			x->r1 += 1;
			if (x->l) x->r1 += x->l->r1;
		}
	}

	// longest 값 갱신
	if (x->val == 1) {
		x->longest = 1;
		if (x->l) x->longest += x->l->r1;
		if (x->r) x->longest += x->r->l1;
	}
	else x->longest = 0;
	if (x->l) x->longest = max(x->longest, x->l->longest);
	if (x->r) x->longest = max(x->longest, x->r->longest);
}

// reverse 연산을 아래에 전파
void push(Node *x) {
	if (x->rev == 0) return;

	if (x->l) {
		x->l->rev ^= 1;
		swap(x->l->l, x->l->r);
		swap(x->l->l1, x->l->r1);
	}
	if (x->r) {
		x->r->rev ^= 1;
		swap(x->r->l, x->r->r);
		swap(x->r->l1, x->r->r1);
	}
	pull(x);
	x->rev = 0;
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

// [lo, hi] 구간을 뒤집음
void reverse(int lo, int hi) {
	if (lo > hi) return;
	Node* now = interval(lo, hi);
	now->rev ^= 1;
	swap(now->l, now->r);
	swap(now->l1, now->r1);
}

int arr[100100];

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
	int n, m;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	init(n);

	scanf("%d", &m);
	while (m--) {
		int t, l, r;
		scanf("%d %d %d", &t, &l, &r);

		if (t == 1) {
			reverse(l, r);
		}
		else {
			printf("%d\n", interval(l, r)->longest);
		}
	}

	return 0;
}
