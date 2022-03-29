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

vector<int> adj[100100];
int parent[100100][18];
int depth[100100];

void add_edge(int u, int v) {
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void dfs(int now) {
	for (int next : adj[now]) {
		if (depth[next] != -1) continue;

		depth[next] = depth[now] + 1;
		parent[next][0] = now;
		dfs(next);
	}
}

void build(int n) {
	memset(depth, -1, sizeof(depth));
	memset(parent, -1, sizeof(parent));

	depth[0] = 0;
	dfs(0);

	for (int k = 0; k < 18 - 1; k++) {
		for (int i = 0; i < n; i++) {
			if (parent[i][k] != -1)
				parent[i][k + 1] = parent[parent[i][k]][k];
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		if (ancu != -1 && depth[ancu] >= depth[v])
			u = ancu;
	}
	if (u == v) return u;

	for (int k = 18 - 1; k >= 0; k--) {
		int ancu = parent[u][k];
		int ancv = parent[v][k];

		if (ancu == ancv) continue;
		u = ancu;
		v = ancv;
	}

	u = parent[u][0];
	return u;
}

int arr[100100];
vector<int> used;

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
	void update(int pv, int now) {
		root[now] = update(arr[now], 1, root[pv], 0, MAX_RANGE);
		for (int nxt : adj[now]) {
			if (nxt == pv) continue;
			update(now, nxt);
		}
	}

	int get_kth(int k, Node *uno, Node *vno, Node *lno, Node *plno, int nl, int nr) {
		if (nl + 1 == nr) return nl;
		int mid = (nl + nr) / 2;
		int lsum = uno->l->val + vno->l->val - lno->l->val - plno->l->val;
		if (lsum >= k)
			return get_kth(k, uno->l, vno->l, lno->l, plno->l, nl, mid);
		else return get_kth(k - lsum, uno->r, vno->r, lno->r, plno->r, mid, nr);

	}
	int get_kth(int k, int u, int v) {
		int lca = LCA(u, v);
		int plca = parent[lca][0];
		return get_kth(k, root[u], root[v], root[lca], root[plca], 0, MAX_RANGE);
	}
}pst;

int main()
{
	int n, m;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		used.push_back(arr[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());
	for (int i = 1; i <= n; i++) {
		arr[i] = lower_bound(used.begin(), used.end(), arr[i]) - used.begin();
	}

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(u, v);
	}
	add_edge(0, 1);

	build(n + 1);
	pst.init();
	pst.update(0, 1);

	scanf("%d", &m);
	while (m--) {
		int u, v, k, res;
		scanf("%d %d %d", &u, &v, &k);
		res = pst.get_kth(k, u, v);
		printf("%d\n", used[res]);
	}

	return 0;
}
