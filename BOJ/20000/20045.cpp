#include <stdio.h>
#include <queue>
#include <memory.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Node {
	Node *l, *r;
	int val;
};

const int MX = 250100;
const int MAXN = 250100;
const int MAX_DEPTH = 19;
const int MAX_NODE = MAXN * 4 + MAX_DEPTH * MAXN;

int cnt = 0;
Node nodes[MAX_NODE];

Node* new_node(){
	return &nodes[cnt++];
}

Node* root[MAXN + 1];
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
	root[0] = build(0, MX);
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
	root[rcnt] = update(idx, val, root[rcnt - 1], 0, MX);
	rcnt++;
}

int query(int l, int r, Node* no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return no->val;
	int mid = (nl + nr) / 2;
	return query(l, r, no->l, nl, mid) + query(l, r, no->r, mid, nr);
}
int query(int k, int l, int r) { return query(l, r, root[k], 0, MX); }

int get_kth(int k, Node* pno, Node* no, int nl, int nr){
	if (no->val - pno->val < k) return -1;
	if (nl + 1 == nr) return nl;
	int mid = (nl + nr) / 2;
	int lsum = no->l->val - pno->l->val;
	if (lsum >= k)
		return get_kth(k, pno->l, no->l, nl, mid);
	else return get_kth(k - lsum, pno->r, no->r, mid, nr);

}
int get_kth(int k, int s, int e){
	return get_kth(k, root[s - 1], root[e], 0, MX);
}


ll arr[MX];
ll psum[MX];

vector<ll> used;
void compress(int n){
	for (int i = 0; i <= n; i++){
		used.push_back(psum[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());
}
int getcx(ll x){
	return lower_bound(used.begin(), used.end(), x) - used.begin();
}

struct QNode{
	int idx, kth;
	ll val;
	bool operator < (const QNode& rhs) const{
		return val < rhs.val;
	}
};
priority_queue<QNode> pq;

int main()
{
	int n, k;

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++){
		scanf("%lld", &arr[i]);
		psum[i] = psum[i - 1] + arr[i];
	}
	compress(n);

	init();
	for (int i = 0; i <= n; i++){
		update(getcx(psum[i]), 1);
	}
	for (int i = 1; i <= n; i++){
		int kth = get_kth(1, 1, i);
		ll val = psum[i] - used[kth];
		pq.push({ i, 1, val });
	}

	for (int i = 0; i < k; i++){
		QNode qn = pq.top(); pq.pop();
		int kth;
		ll newv;

		printf("%lld ", qn.val);

		kth = get_kth(qn.kth + 1, 1, qn.idx);
		if (kth == -1) continue;
		newv = psum[qn.idx] - used[kth];
		pq.push({ qn.idx, qn.kth + 1, newv });
	}
	printf("\n");
	return 0;
}
