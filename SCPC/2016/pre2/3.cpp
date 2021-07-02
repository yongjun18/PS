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

int cnt1[MX];
int cnt0[MX];

int tree1[MX * 4];
int tree0[MX * 4];
int trmax[MX * 4];

void build(int no, int nl, int nr){
	if (nl + 1 == nr){
		tree1[no] = cnt1[nl];
		tree0[no] = cnt0[nl];
		trmax[no] = max(cnt1[nl], cnt0[nl]);
		return;
	}
	int mid = (nl + nr) / 2;
	build(2 * no, nl, mid);
	build(2 * no + 1, mid, nr);
	tree1[no] = tree1[2 * no] + tree1[2 * no + 1];
	tree0[no] = tree0[2 * no] + tree0[2 * no + 1];
	trmax[no] = max(
		trmax[2 * no] + tree0[2 * no + 1],
		trmax[2 * no + 1] + tree1[2 * no]);
}
void build(int n){ build(1, 0, n); }

void update(int idx, int val, int no, int nl, int nr){
	if (idx < nl || nr <= idx) return;
	if (nl + 1 == nr){
		if (val == 1){
			cnt1[idx]++;
			cnt0[idx]--;
		}
		else{
			cnt1[idx]--;
			cnt0[idx]++;
		}
		tree1[no] = cnt1[nl];
		tree0[no] = cnt0[nl];
		trmax[no] = max(cnt1[nl], cnt0[nl]);
		return;
	}

	int mid = (nl + nr) / 2;
	update(idx, val, 2 * no, nl, mid);
	update(idx, val, 2 * no + 1, mid, nr);
	tree1[no] = tree1[2 * no] + tree1[2 * no + 1];
	tree0[no] = tree0[2 * no] + tree0[2 * no + 1];
	trmax[no] = max(
		trmax[2 * no] + tree0[2 * no + 1],
		trmax[2 * no + 1] + tree1[2 * no]);
}
void update(int idx, int val, int n){ update(idx, val, 1, 0, n); }

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
		build(mx);
		ans = trmax[1];

		for (auto it : pt){
			int x = it.x;
			int type = it.type;
			update(x, type ^ 1, mx);
			ans = max(ans, trmax[1]);
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
