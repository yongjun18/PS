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
	double w;
	bool operator <(const Edge &ot) const { return w < ot.w; }
};

vector<Edge> edges;
vector<Edge> mst;

double kruskal(int n) {
	double sum = 0;
	DisjointSet ds;

	ds.init(n);
	sort(edges.begin(), edges.end());

	for (int i = 0; i < edges.size(); i++) {
		if (mst.size() == n - 1) break;
		Edge now = edges[i];

		if (ds.find(now.u) == ds.find(now.v)) continue;
		ds.merge(now.u, now.v);
		sum += now.w;

		mst.push_back(now);
	}
	return sum;
}

int n, m;
ll f;
int u[10100];
int v[10100];
ll c[10100];
ll t[10100];

int solve(double mid) {
	edges.clear();
	mst.clear();
	for (int i = 0; i < m; i++) {
		edges.push_back({ u[i], v[i], c[i] + mid * t[i] });
	}
	if (kruskal(n) <= f) return 1;
	return 0;
}

double parametric_search(double x, double y) {
	double lo = x;
	double hi = y;
	for (int i = 0; i < 128; i++) {
		double mid = (lo + hi) / 2;
		if (solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	scanf("%d %d %lld", &n, &m, &f);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %lld %lld", &u[i], &v[i], &c[i], &t[i]);
		u[i]--;
		v[i]--;
	}
	printf("%.4lf\n", parametric_search(0, f));
	return 0;
}
