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

const int MX = 100100;

ll tree[4 * MX];
ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = max(tree[no], val);
	int mid = (nl + nr) / 2;
	return tree[no] = max(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }

int li[100100];
int ri[100100];

vector<int> adj[100100];

int main()
{
	int n;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		li[x] = i;
	}
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		ri[x] = i;
	}
	
	for (int i = 1; i <= n; i++){
		int x = max(1, i - 4);
		int y = min(n, i + 4);
		for (int j = x; j <= y; j++){
			adj[li[i]].push_back(ri[j]);
		}
	}
	for (int i = 0; i < n; i++){
		sort(adj[i].rbegin(), adj[i].rend());
	}

	for (int i = 0; i < n; i++){
		for (int nxt : adj[i]){
			ll tmp = query(0, nxt) + 1;
			update(nxt, tmp);
		}
	}

	printf("%lld\n", tree[1]);
	return 0;
}
