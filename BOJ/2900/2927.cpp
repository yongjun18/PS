#include <stdio.h>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;
typedef long long ll;

struct DisjointSet{
	vector<int> parent, siz;

	void init(int n){
		parent = vector<int>(n, 0);
		siz = vector<int>(n, 1);
		for (int i = 0; i < n; i++){
			parent[i] = i;
		}
	}
	int find(int u){
		if (parent[u] == u) return u;
		return parent[u] = find(parent[u]);
	}
	void merge(int u, int v){
		u = find(u);
		v = find(v);
		if (siz[u] < siz[v]) swap(u, v);
		parent[v] = u;
		siz[u] += siz[v];
	}
};
DisjointSet ds;

const int MX = 30100;
int tree[MX * 4];

int seg_update(int idx, int val, int no, int nl, int nr){
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = seg_update(idx, val, 2 * no, nl, mid)
		+ seg_update(idx, val, 2 * no + 1, mid, nr);
}
void seg_update(int idx, int val, int n = MX){
	seg_update(idx, val, 1, 0, n);
}
int seg_query(int l, int r, int no, int nl, int nr){
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return seg_query(l, r, 2 * no, nl, mid) + seg_query(l, r, 2 * no + 1, mid, nr);
}
int seg_query(int l, int r, int n = MX){
	return seg_query(l, r, 1, 0, n);
}

vector<int> adj[MX];

int pcnt = 0;
vector<int> pos, parent, heavy, head, depth;

int dfs(int now){
	int maxsiz = 0;
	int maxc = -1;
	int siz = 1;

	for (int nxt : adj[now]){
		if (nxt == parent[now]) continue;
		parent[nxt] = now;
		depth[nxt] = depth[now] + 1;
		int nxtsiz = dfs(nxt);
		siz += nxtsiz;
		if (maxsiz < nxtsiz){
			maxsiz = nxtsiz;
			maxc = nxt;
		}
	}
	heavy[now] = maxc;
	return siz;
}
void decompose(int now, int h){
	pos[now] = pcnt++;
	head[now] = h;

	if (heavy[now] != -1)
		decompose(heavy[now], h);

	for (int nxt : adj[now]){
		if (nxt == parent[now]) continue;
		if (nxt == heavy[now]) continue;
		decompose(nxt, nxt);
	}
}
void update(int v, int val){
	seg_update(pos[v], val);
}
int query(int u, int v){
	int ret = 0;
	
	for (; head[u] != head[v]; v = parent[head[v]]){
		if (depth[head[u]] > depth[head[v]]) swap(u, v);
		int path_sum = seg_query(pos[head[v]], pos[v] + 1);
		ret += path_sum;
	}
	if (depth[u] > depth[v]) swap(u, v);
	ret += seg_query(pos[u], pos[v] + 1);

	return ret;
}

void init(int n = MX){
	parent = vector<int>(n);
	heavy = vector<int>(n);
	depth = vector<int>(n);
	head = vector<int>(n);
	pos = vector<int>(n);

	parent[1] = -1;
	depth[1] = 0;
	dfs(1);

	decompose(1, 1);
}

int arr[MX];

struct Query{
	int t, a, b;
};
vector<Query> qry;

int main()
{
	int n, q;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++){
		char c;
		int t, a, b;
		scanf(" %c %*s %d %d", &c, &a, &b);
		if (c == 'b') t = 1;
		if (c == 'p') t = 2;
		if (c == 'e') t = 3;
		qry.push_back({ t, a, b });
	}

	ds.init(n + 5);
	for (Query &it : qry){
		if (it.t == 1){
			if (ds.find(it.a) != ds.find(it.b)){
				adj[it.a].push_back(it.b);
				adj[it.b].push_back(it.a);
				ds.merge(it.a, it.b);
			}
		}
	}
	for (int i = 2; i <= n; i++){
		if (ds.find(i) != ds.find(1)){
			adj[i].push_back(1);
			adj[1].push_back(i);
			ds.merge(1, i);
		}
	}
	init();
	for (int i = 1; i <= n; i++){
		update(i, arr[i]);
	}

	ds.init(n + 5);
	for (Query &it : qry){
		if (it.t == 1){
			if (ds.find(it.a) != ds.find(it.b)){
				ds.merge(it.a, it.b);
				printf("yes\n");
			}
			else printf("no\n");
		}
		if (it.t == 2){
			update(it.a, it.b);
		}
		if (it.t == 3){
			if (ds.find(it.a) == ds.find(it.b)){
				printf("%d\n", query(it.a, it.b));
			}
			else{
				printf("impossible\n");
			}
		}
	}

	return 0;
}
