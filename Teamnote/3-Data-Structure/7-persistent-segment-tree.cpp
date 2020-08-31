// O(NlogN)

struct Node {
	Node *l, *r;
	int val;
};
vector<Node*> used;
Node* new_node(){
	used.push_back(new Node());
	return used.back();
}

// MX : 최대 구간 크기
const int MX = 100001;
// MAXN : 최대 갱신 횟수
const int MAXN = 10000;
Node* root[MAXN + 1];
int rcnt;

// 0번 트리 빌드
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
	for(Node* it : used) delete(it);
	used.clear();
	root[0] = build(0, MX);
	rcnt = 1;
}

// shadow : 현재 위치의 이전 버전 노드
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
// k번 트리의 [l, r)구간 합
int query(int k, int l, int r) { return query(l, r, root[k], 0, MX); }
