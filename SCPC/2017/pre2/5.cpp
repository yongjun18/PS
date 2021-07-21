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

const int MX = 200100;

struct Seg{
	ll tree[4 * MX];
	ll build(int no, int nl, int nr) {
		if (nl + 1 == nr) return tree[no] = INF;
		int mid = (nl + nr) / 2;
		return tree[no] = min(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
	}
	ll build(int n) { return build(1, 0, n); }
	ll query(int l, int r, int no, int nl, int nr) {
		if (r <= nl || nr <= l) return INF;
		if (l <= nl && nr <= r) return tree[no];
		int mid = (nl + nr) / 2;
		return min(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
	}
	ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }
	ll update(int idx, ll val, int no, int nl, int nr) {
		if (idx < nl || nr <= idx) return tree[no];
		if (nl + 1 == nr && nl == idx) return tree[no] = min(val, tree[no]);
		int mid = (nl + nr) / 2;
		return tree[no] = min(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
	}
	ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }
};

Seg dp, dp2;

struct Stick{
	int x, y, w;
	bool operator < (const Stick &rhs) const{
		return x > rhs.x;
	}
};

vector<Stick> arr;
vector<int> usec;
vector<Stick> stick[MX];

void compress(){
	usec.clear();
	usec.push_back(-1);
	for (int i = 0; i < arr.size(); i++){
		usec.push_back(arr[i].x);
		usec.push_back(arr[i].y);
	}
	sort(usec.begin(), usec.end());
	usec.erase(unique(usec.begin(), usec.end()), usec.end());

	for (int i = 0; i < arr.size(); i++){

		arr[i].x = lower_bound(usec.begin(), usec.end(), arr[i].x) - usec.begin();
		arr[i].y = lower_bound(usec.begin(), usec.end(), arr[i].y) - usec.begin();
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, mx;
		int maxx;

		scanf("%d", &n);
		arr.clear();

		for (int i = 0; i < n; i++){
			int x, y, w;
			scanf("%d %d %d", &x, &y, &w);
			arr.push_back({ x, y, w });
		}
		compress();
		mx = usec.size();
		for (int i = 0; i < mx; i++){
			stick[i].clear();
		}

		for (int i = 0; i < n; i++){
			stick[arr[i].y].push_back(arr[i]);
		}
		for (int i = 0; i < mx; i++){
			sort(stick[i].begin(), stick[i].end());
		}

		dp.build(mx);
		dp2.build(mx);
		dp2.update(0, 0, mx);

		maxx = 0;
		for (int i = 0; i < mx; i++){
			if (stick[i].size() == 0){
				if (i == 0) dp2.update(i, 0, mx);
				else dp2.update(i, dp2.query(i - 1, i, mx), mx);
				continue;
			}

			for (int j = 0; j < stick[i].size(); j++){
				int x = stick[i][j].x;
				int y = stick[i][j].y;
				int w = stick[i][j].w;
				maxx = max(maxx, x);

				ll tmp = dp2.query(x - 1, y + 1, mx) + w;
				dp2.update(y, tmp, mx);
				dp.update(y, tmp, mx);

				dp2.update(y, dp.query(maxx, y + 1, mx), mx);
			}
		}

		printf("Case #%d\n", test);
		printf("%lld\n", dp2.query(mx - 1, mx, mx));
	}

	return 0;
}
