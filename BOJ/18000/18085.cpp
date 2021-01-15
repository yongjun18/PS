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

DisjointSet ds;
map<int, vector<int> > mp;
vector< pair< pair<int, int>, int > > ans;

int main()
{
	int n;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++){
		int m;
		scanf("%d", &m);
		while (m--){
			int x;
			scanf("%d", &x);
			mp[x].push_back(i);
		}
	}

	ds.init(n + 1);
	for (auto& it : mp){
		int x = it.first;
		for (int i = 0; i + 1 < it.second.size(); i++){
			int n1 = it.second[i];
			int n2 = it.second[i + 1];
			if (ds.find(n1) != ds.find(n2)){
				ds.merge(n1, n2);
				ans.push_back({ { n1, n2 }, x });
			}
		}
	}

	if (ds.size[ds.find(1)] != n){
		printf("impossible\n");
	}
	else{
		for (auto it : ans){
			printf("%d %d %d\n", it.first.first, it.first.second, it.second);
		}
	}

	return 0;
}
