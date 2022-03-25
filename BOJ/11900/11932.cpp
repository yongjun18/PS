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

	static const int MAX_RANGE = 100100;
	static const int MAX_N = 100100;
	static const int MAX_DEPTH = 18;
	static const int MAX_NODE = MAX_RANGE * 2 + MAX_DEPTH * MAX_N;

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


	int get_kth(int k, vector< pair<Node*, Node*> > &rg2, int nl, int nr) {
		if (nl + 1 == nr) return nl;
		int mid = (nl + nr) / 2;
		int lsum = 0;
		for (auto[pno, no] : rg2) {
			lsum += no->l->val - pno->l->val;
		}
		if (lsum >= k) {
			for (auto &it : rg2) {
				it.first = it.first->l;
				it.second = it.second->l;
			}
			return get_kth(k, rg2, nl, mid);
		}
		else {
			for (auto &it : rg2) {
				it.first = it.first->r;
				it.second = it.second->r;
			}
			return get_kth(k - lsum, rg2, mid, nr);
		}
	}
	int get_kth(int k, vector< pair<int, int> > &rg) {
		vector< pair<Node*, Node*> > rg2;
		for (auto[s, e] : rg) {
			rg2.push_back({ root[s - 1], root[e] });
		}
		return get_kth(k, rg2, 0, MAX_RANGE);
	}
} pst;

const int MX = 100100;

vector<int> adj[MX];

vector<int> order;
vector<int> parent, depth, heavy, head, pos;
int pcnt;

int dfs(int v) {
	int size = 1;
	int max_child_size = 0;

	for (int next : adj[v]) if (next != parent[v]) {
		parent[next] = v;
		depth[next] = depth[v] + 1;

		int next_size = dfs(next);
		size += next_size;

		if (max_child_size < next_size) {
			max_child_size = next_size;
			heavy[v] = next;
		}
	}
	return size;
}

void decompose(int v, int h) {
	head[v] = h;
	pos[v] = pcnt++;
	order.push_back(v);

	if (heavy[v] != -1)
		decompose(heavy[v], h);

	for (int next : adj[v]) if (next != parent[v]) {
		if (next != heavy[v])
			decompose(next, next);
	}
}

void init(int n = MX) {
	parent = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	pcnt = 1;

	dfs(0);
	decompose(0, 0);
}

void query(int u, int v, int k, vector< pair<int, int> >& rg) {
	for (; head[u] != head[v]; v = parent[head[v]]) {
		if (depth[head[u]] > depth[head[v]])
			swap(u, v);
		rg.push_back({ pos[head[v]], pos[v] });
	}

	if (depth[u] > depth[v])
		swap(u, v);
	rg.push_back({ pos[u], pos[v] });
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
	for (int i = 0; i < n; i++) {
		arr[i] = lower_bound(used.begin(), used.end(), arr[i]) - used.begin();
	}

	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		x--; y--;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	init();

	pst.init();
	for (int it : order) {
		pst.update(arr[it], 1);
	}


	while (m--) {
		int x, y, k, res;
		vector< pair<int, int> > rg;
		scanf("%d %d %d", &x, &y, &k);
		x--; y--;
		query(x, y, k, rg);

		res = pst.get_kth(k, rg);
		printf("%d\n", used[res]);
	}
	return 0;
}
