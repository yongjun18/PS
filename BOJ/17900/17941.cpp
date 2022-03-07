#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 505;

struct Seg {
	int n;
	int arr[MX];
	int tree[2 * MX];

	void build() {
		for (int i = 0; i < n; i++)
			tree[n + i] = arr[i];
		for (int i = n - 1; i > 0; i--)
			tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) {
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = max(res, tree[l++]);
			if (r & 1) res = max(res, tree[--r]);
		}
		return res;
	}
};

int arr[MX][MX];
Seg ver[MX];
Seg hor[MX];

int compute(vector<int>& vec, int wsiz) {
	int ret;
	int x = 0;
	int y = wsiz - 1;
	deque<int> dq;

	for (int i = x; i <= y; i++) {
		while (dq.size() > 0 && vec[dq.back()] <= vec[i]) 
			dq.pop_back();
		dq.push_back(i);
	}
	ret = vec[dq.front()];

	while (y + 1 < vec.size()) {
		x++; y++;
		while (dq.size() > 0 && dq.front() < x)
			dq.pop_front();
		while (dq.size() > 0 && vec[dq.back()] < vec[y])
			dq.pop_back();
		dq.push_back(y);
		ret ^= vec[dq.front()];
	}
	return ret;
}


int main() {
	int n, m;
	int q;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		hor[i].n = m;
		for (int j = 0; j < m; j++) {
			hor[i].arr[j] = arr[i][j];
		}
		hor[i].build();
	}
	for (int j = 0; j < m; j++) {
		ver[j].n = n;
		for (int i = 0; i < n; i++) {
			ver[j].arr[i] = arr[i][j];
		}
		ver[j].build();
	}

	scanf("%d", &q);
	while (q--) {
		int x, y, r, c, k, d;
		vector<int> vec;
		scanf("%d %d %d %d %d %d", &x, &y, &r, &c, &k, &d);
		x--; y--;

		if (d == 2) { x -= k - 1; d = 1; }
		if (d == 4) { y -= k - 1; d = 3; }

		if (d == 1) {
			for (int i = x; i < x + k - 1 + r; i++) {
				vec.push_back(hor[i].query(y, y + c));
			}
			printf("%d\n", compute(vec, r));
		}
		else {
			for (int i = y; i < y + k - 1 + c; i++) {
				vec.push_back(ver[i].query(x, x + r));
			}
			printf("%d\n", compute(vec, c));
		}
	}
	return 0;
}
