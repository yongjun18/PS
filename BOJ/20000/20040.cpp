#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

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

DisjointSet ds;

int main()
{
	int n, m;
	int ans;

	scanf("%d %d", &n, &m);
	ds.init(n+1);

	ans = 0;
	for(int i=1; i<=m; i++){
		int x, y;
		scanf("%d %d", &x, &y);

		if(ds.find(x) == ds.find(y)){
			ans = i;
			break;
		}
		ds.merge(x, y);
	}
	printf("%d\n", ans);
	return 0;
}
