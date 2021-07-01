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

int arr[MX];
int tree[4 * MX];
int lazy[4 * MX];

int build(int no, int nl, int nr){
	lazy[no] = 0;
	if (nl + 1 == nr) return tree[no] = arr[nl];
	int mid = (nl + nr) / 2;
	return tree[no] = max(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
}
int build(int n){ return build(1, 0, n); }

void propagate(int no, int nl, int nr){
	if (nl + 1 != nr){
		int mid = (nl + nr) / 2;
		tree[2 * no] += lazy[no];
		tree[2 * no + 1] += lazy[no];
		lazy[2 * no] += lazy[no];
		lazy[2 * no + 1] += lazy[no];
	}
	lazy[no] = 0;
}

void update(int l, int r, int val, int no, int nl, int nr){
	if (r <= nl || nr <= l) return;
	if (l <= nl && nr <= r){
		tree[no] += val;
		lazy[no] += val;
		return;
	}
	propagate(no, nl, nr);
	int mid = (nl + nr) / 2;
	update(l, r, val, 2 * no, nl, mid);
	update(l, r, val, 2 * no + 1, mid, nr);
	tree[no] = max(tree[2 * no], tree[2 * no + 1]);
}
void update(int l, int r, int val, int n){ update(l, r, val, 1, 0, n); }

int query(int l, int r, int no, int nl, int nr){
	if (r <= nl || nr <= l) return -INF;
	if (l <= nl && nr <= r) return tree[no];
	propagate(no, nl, nr);
	int mid = (nl + nr) / 2;
	return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
int query(int l, int r, int n) { return query(l, r, 1, 0, n); }

int cnt1[MX];
int cnt0[MX];
int psum1[MX];
int psum0[MX];

struct Point{
	int x, y, type;
	bool operator < (const Point& rhs) const{
		return y < rhs.y;
	}
};

vector<Point> pt;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, mx;
		int ans;

		scanf("%d", &n);

		mx = n + 5;
		pt.clear();
		for (int i = 0; i < mx; i++){
			cnt1[i] = cnt0[i] = 0;
			psum1[i] = psum0[i] = 0;
		}

		for (int i = 0; i < n; i++){
			int x, y, type;
			scanf("%d %d %d", &x, &y, &type);
			pt.push_back({ x, y, type });
		}
		sort(pt.begin(), pt.end());

		for (auto it : pt){
			if (it.type == 1) cnt1[it.x]++;
			else cnt0[it.x]++;
		}
		psum1[0] = cnt1[0];
		psum0[mx - 1] = cnt0[mx - 1];
		for (int i = 1; i < mx; i++){
			psum1[i] = psum1[i - 1] + cnt1[i];
		}
		for (int i = mx - 2; i >= 0; i--){
			psum0[i] = psum0[i + 1] + cnt0[i];
		}

		arr[0] = psum0[0];
		for (int i = 1; i < mx; i++){
			arr[i] = psum0[i] + psum1[i - 1];
		}
		build(mx);
		ans = tree[1];

		for (auto it : pt){
			int x = it.x;
			int type = it.type;

			if (type == 1){
				update(x + 1, mx, -1, mx);
				update(0, x + 1, 1, mx);
			}
			else{
				update(x + 1, mx, 1, mx);
				update(0, x + 1, -1, mx);
			}
			ans = max(ans, tree[1]);
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
