#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct DisjointSet {
	vector<int> parent, size;

	void init(int n) {
		parent = vector<int>(n);
		size = vector<int>(n, 1);
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int find(int u) {
		if (u == parent[u]) return u;
		return parent[u] = find(parent[u]);
	}

	void merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) return;
		if (size[u] < size[v]) swap(u, v);
		parent[v] = u;
		size[u] += size[v];
	}
};

struct Edge {
	int u, v;
	pair<int, int> w;
	int chosen;
	bool operator <(const Edge &ot) const { return w < ot.w; }
};

vector<Edge> edges;
vector<Edge> mst;

int kruskal(int n) {
	DisjointSet ds;

	ds.init(n);
	sort(edges.begin(), edges.end());

	for (int i = 0; i < edges.size(); i++) {
		if (mst.size() == n - 1) break;
		Edge &now = edges[i];

		if (ds.find(now.u) == ds.find(now.v)) continue;
		ds.merge(now.u, now.v);

		mst.push_back(now);
		now.chosen = 1;
	}
	if (mst.size() == n - 1) return 1;
	else return 0;
}

int ans[55];

int main()
{
	int n, m;
	int ok = 1;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char c;
			scanf(" %c", &c);
			if (c == 'Y' && i < j) {
				edges.push_back({ i, j, {i, j}, 0 });
			}
		}
	}

	if (kruskal(n) == 0) {
		ok = 0;
	}

	for (Edge& it : edges) {
		if (mst.size() >= m) break;
		if (it.chosen == 0) {
			mst.push_back(it);
			it.chosen = 1;
		}
	}
	if (mst.size() < m) {
		ok = 0;
	}

	if (ok) {
		for (Edge &it : mst) {
			ans[it.u]++;
			ans[it.v]++;
		}
		for (int i = 0; i < n; i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	else printf("-1\n");

	return 0;
}
