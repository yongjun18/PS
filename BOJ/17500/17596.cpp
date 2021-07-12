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
const ll INF = 1e15;
const int MOD = 1e9 + 7;

const int MX = 100100;

struct Node{
	ll minv, maxv;
	ll tree1, tree2;
	Node(){}
	Node(ll mn, ll mx, ll t1, ll t2){
		minv = mn; maxv = mx;
		tree1 = t1; tree2 = t2;
	}
};

Node merge(Node n1, Node n2){
	Node ret;
	
	ret.minv = min(n1.minv, n2.minv);
	ret.maxv = max(n1.maxv, n2.maxv);
	
	ret.tree1 = max(n1.tree1, n2.tree1);
	ret.tree1 = max(ret.tree1, n2.maxv - n1.minv);

	ret.tree2 = max(n1.tree2, n2.tree2);
	ret.tree2 = max(ret.tree2, n1.maxv - n2.minv);

	return ret;
}

struct Seg{
	Node nodes[4 * MX];

	Node update(int idx, ll val, int no, int nl, int nr){
		if (idx < nl || nr <= idx) return nodes[no];
		if (nl + 1 == nr) return nodes[no] = Node(val, val, 0, 0);
		int mid = (nl + nr) / 2;
		return nodes[no] = merge(update(idx, val, 2 * no, nl, mid), 
			update(idx, val, 2 * no + 1, mid, nr));
	}
	void update(int idx, ll val, int n = MX){
		update(idx, val, 1, 0, n);
	}

	Node query(int l, int r, int no, int nl, int nr){
		if (r <= nl || nr <= l) return Node(INF, -INF, 0, 0);
		if (l <= nl && nr <= r) return nodes[no];
		int mid = (nl + nr) / 2;
		return merge(query(l, r, 2 * no, nl, mid),
			query(l, r, 2 * no + 1, mid, nr));
	}
	Node query(int l, int r, int n = MX){
		return query(l, r, 1, 0, n);
	}
};

Seg seg[7];

int main()
{
	int n, q;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		ll vi, di;
		int idx;
		scanf("%lld %lld", &vi, &di);
		
		idx = ((1 - i) % 7 + 7) % 7;
		for (int j = 0; j < 7; j++){
			ll val = vi + (3 - abs(3 - j)) * di;
			seg[(idx + j) % 7].update(i, val);
		}
	}

	scanf("%d", &q);
	while (q--){
		int s, t;
		scanf("%d %d", &s, &t);

		if (s < t){
			int idx = ((1 - s) % 7 + 7) % 7;
			Node res = seg[idx].query(s, t + 1);
			printf("%lld\n", res.tree1);
		}
		else{
			int idx = ((-s) % 7 + 7) % 7;
			Node res = seg[idx].query(t, s + 1);
			printf("%lld\n", res.tree2);
		}
	}

	return 0;
}
