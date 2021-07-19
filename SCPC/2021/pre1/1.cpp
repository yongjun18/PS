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
int arr[100100];
int vis[100100];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		int ans;

		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%d", &arr[i]);
		}
		ds.init(n + 1);
		for (int i = 0; i < n + 5; i++){
			vis[i] = 0;
		}

		for (int i = 1; i <= n; i++){
			if (i + arr[i] <= n){
				ds.merge(i, i + arr[i]);
			}
		}

		ans = 0;
		for (int i = 1; i <= n; i++){
			if (vis[ds.find(i)] == 0){
				ans++;
				vis[ds.find(i)] = 1;
			}
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
