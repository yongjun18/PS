#include <stdio.h>
#include <queue>
#include <memory.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const ll INF = 1e16;
const int MOD = 1e9 + 7;

struct Node {
	Node *l, *r;
	int val;
};
Node* new_node(){
	return new Node();
}

const int MX = 250100;
const int MAXN = 250100;
Node* root[MAXN + 1];
int rcnt;

Node* build(int nl, int nr) {
	Node* now = new_node();
	if (nl + 1 < nr) {
		int mid = (nl + nr) / 2;
		now->l = build(nl, mid);
		now->r = build(mid, nr);
		now->val = 0;
	}
	return now;
}

void init() {
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

int get_mth_in_k(int m, Node* no, int nl, int nr){
	if (no->val < m) return -1;
	if (nl + 1 == nr) return nl;
	int mid = (nl + nr) / 2;
	if (no->l->val >= m) return get_mth_in_k(m, no->l, nl, mid);
	else return get_mth_in_k(m - no->l->val, no->r, mid, nr);
}
int get_mth_in_k(int k, int m){ return get_mth_in_k(m, root[k], 0, MX); }


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
	int idx, mth;
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
		int mth = get_mth_in_k(i, 1);
		ll val = psum[i] - used[mth];
		pq.push({ i, 1, val });
	}

	for (int i = 0; i < k; i++){
		QNode qn = pq.top(); pq.pop();
		int mth;
		ll newv;
		
		printf("%lld ", qn.val);
		
		mth = get_mth_in_k(qn.idx, qn.mth + 1);
		if (mth == -1) continue;
		newv = psum[qn.idx] - used[mth];
		pq.push({ qn.idx, qn.mth + 1, newv });
	}
	return 0;
}
