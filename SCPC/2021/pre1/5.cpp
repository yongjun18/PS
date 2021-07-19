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
	vector<int> parent, size, val, lazy, conf;

	void init(int n) {
		parent = vector<int>(n);
		size = vector<int>(n, 1);
		val = vector<int>(n, 0);
		lazy = vector<int>(n, 0);
		conf = vector<int>(n, 0);
		for (int i = 0; i < n; i++) parent[i] = i;
	}
	int find(int u, int idx) {
		if (u == parent[u]) {
			parent[idx] = u;
			return u;
		}
		val[idx] += lazy[parent[u]];
		lazy[idx] += lazy[parent[u]];
		return find(parent[u], idx);
	}
	void merge(int u, int v, int d) {
		int up, vp, lazyv;
		up = find(u, u); vp = find(v, v);
		
		if (up == vp) {
			if (val[u] - val[v] != d){
				conf[up] = 1;
			}
			return;
		}

		if (conf[up] == 1 || conf[vp] == 1){
			conf[up] = conf[vp] = 1;
		}
		if (size[up] < size[vp]) {
			swap(up, vp);
			swap(u, v);
			d *= -1;
		}

		parent[vp] = up;
		size[up] += size[vp];
		lazyv = val[u] - val[v] - d;
		val[vp] += lazyv;
		lazy[vp] += lazyv;
	}
};
DisjointSet ds;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, k;

		scanf("%d %d", &n, &k);
		ds.init(n + 5);
		
		printf("Case #%d\n", test);
		for (int i = 0; i < k; i++){
			int type, x, y, d;
			int xp, yp;
			scanf("%d", &type);
			
			if (type == 1){
				scanf("%d %d %d", &x, &y, &d);
				ds.merge(x, y, d);
			}
			else{
				scanf("%d %d", &x, &y);
				xp = ds.find(x, x);
				yp = ds.find(y, y);
				
				if (xp != yp){
					printf("NC\n");
				}
				else if (ds.conf[xp]){
					printf("CF\n");
				}
				else{
					printf("%d\n", ds.val[x] - ds.val[y]);
				}
			}
		}
	}

	return 0;
}
