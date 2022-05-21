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
	char val;
};

Node *root;

void pull(Node *x) {
	x->siz = 1;
	if (x->l) x->siz += x->l->siz;
	if (x->r) x->siz += x->r->siz;
}

// reverse 연산을 아래에 전파
void push(Node *x) {
	if (x->rev == 0) return;
	swap(x->l, x->r);
	if (x->l) x->l->rev ^= 1;
	if (x->r) x->r->rev ^= 1;
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
	interval(lo, hi)->rev ^= 1;
}

// [lo, hi] 구간을 cnt번 왼쪽으로 shift
void shift(int lo, int hi, int cnt) {
	reverse(lo, lo + cnt - 1);
	reverse(lo + cnt, hi);
	reverse(lo, hi);
}

void inorder(Node* now) {
	push(now);
	if (now->l) inorder(now->l);
	printf("print %c\n", now->val);
	if (now->r) inorder(now->r);
}

char str[100100];

void init() {
	Node* now = root = new Node();
	for (int i = 0; str[i]; i++) {
		now->r = new Node();
		now->r->par = now;
		now->r->val = str[i];
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
	int n, q;
	scanf("%s", str);
	n = strlen(str);
	init();

	scanf("%d", &q);
	while (q--) {
		int t, x, y;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d %d", &x, &y);
			x++; y++;
			shift(1, y, x - 1);
		}
		if (t == 2) {
			scanf("%d %d", &x, &y);
			x++; y++;
			shift(x, n, y - x + 1);
		}
		if (t == 3) {
			scanf("%d", &x);
			x++;
			get_kth(x);
			printf("%c\n", root->val);
		}
		//inorder(root);
	}

	return 0;
}
