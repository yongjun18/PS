const int INF = 1e9;
const int MX = 1e5;

ll tree[400000];
ll lazy[400000];

void propagate(int no, int nl, int nr) {
	if (lazy[no] == 0) return;
	if (nl + 1 != nr) {
		lazy[2 * no] += lazy[no];
		lazy[2 * no + 1] += lazy[no];
	}
	tree[no] += lazy[no] * (nr - nl);
	lazy[no] = 0;
}
ll seg_query(int l, int r, int no, int nl, int nr) {
	propagate(no, nl, nr);
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];

	int mid = (nl + nr) / 2;
	return seg_query(l, r, 2 * no, nl, mid) + seg_query(l, r, 2 * no + 1, mid, nr);
}
ll seg_query(int l, int r, int n) { return seg_query(l, r, 1, 0, n); }
ll seg_update(int l, int r, ll val, int no, int nl, int nr) {
	propagate(no, nl, nr);
	if (r <= nl || nr <= l) return tree[no];
	if (l <= nl && nr <= r) {
		lazy[no] += val;
		propagate(no, nl, nr);
		return tree[no];
	}
	int mid = (nl + nr) / 2;
	return tree[no] = seg_update(l, r, val, 2 * no, nl, mid) + seg_update(l, r, val, 2 * no + 1, mid, nr);
}
ll seg_update(int l, int r, ll val, int n) { return seg_update(l, r, val, 1, 0, n); }

vector<int> adj[MX];
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

	if (heavy[v] != -1)
		decompose(heavy[v], h);

	for (int next : adj[v]) if (next != parent[v]) {
		if (next != heavy[v])
			decompose(next, next);
	}
}

void init(int n) {
	parent = vector<int>(n);
	depth = vector<int>(n);
	heavy = vector<int>(n, -1);
	head = vector<int>(n);
	pos = vector<int>(n);
	pcnt = 0;

	dfs(0);
	decompose(0, 0);
}

void update(int u, int v, int c) {
	for (; head[u] != head[v]; v = parent[head[v]]) {
		if (depth[head[u]] > depth[head[v]])
			swap(u, v);
		seg_update(pos[head[v]], pos[v] + 1, c, MX);
	}

	if (depth[u] > depth[v])
		swap(u, v);
	seg_update(pos[u] + 1, pos[v] + 1, c, MX);
}

ll query(int u, int v) {
	ll sum = 0;

	for (; head[u] != head[v]; v = parent[head[v]]) {
		if (depth[head[u]] > depth[head[v]])
			swap(u, v);
		sum += seg_query(pos[head[v]], pos[v] + 1, MX);
	}

	if (depth[u] > depth[v])
		swap(u, v);
	sum += seg_query(pos[u] + 1, pos[v] + 1, MX);
	return sum;
}
