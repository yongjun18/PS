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

const int MX = 500100;
int mx;
int tree[2 * MX];

void init(){
	for (int i = 0; i < 2 * mx; i++){
		tree[i] = INF;
	}
}
void update(int idx, int val){
	idx += mx;
	for (tree[idx] = min(tree[idx], val); idx > 1; idx >>= 1){
		tree[idx >> 1] = min(tree[idx], tree[idx ^ 1]);
	}
}
int query(int l, int r){
	int ret = INF;
	for (l += mx, r += mx; l < r; l >>= 1, r >>= 1){
		if (l & 1) ret = min(ret, tree[l++]);
		if (r & 1) ret = min(ret, tree[--r]);
	}
	return ret;
}

struct Point{
	int x, y, xy, idx;
};
vector<Point> pt;

int result[MX];

int cmpx(const Point &p1, const Point &p2){
	return p1.x < p2.x;
}
int cmpy(const Point &p1, const Point &p2){
	return p1.y < p2.y;
}

void compress(){
	vector<int> used;
	for (int i = 0; i < pt.size(); i++){
		used.push_back(pt[i].xy);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < pt.size(); i++){
		int pos = lower_bound(used.begin(), used.end(), pt[i].xy) - used.begin();
		pt[i].xy = pos;
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int m, n;
		int nxt;
		ll ans;

		scanf("%d %d", &m, &n);
		mx = n + 5;

		pt.clear();
		for (int i = 0; i < n; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			pt.push_back({ x, y, x - y, i });
		}
		compress();

		for (int i = 0; i < n; i++){
			result[i] = min(m - pt[i].x, m - pt[i].y);
		}

		sort(pt.begin(), pt.end(), cmpx);
		nxt = n - 1;
		init();
		for (int i = n - 1; i >= 0; i--){
			while (pt[i].x < pt[nxt].x){
				update(pt[nxt].xy, pt[nxt].y);
				nxt--;
			}
			int miny = query(0, pt[i].xy + 1);
			result[pt[i].idx] = min(result[pt[i].idx], miny - pt[i].y);
		}

		sort(pt.begin(), pt.end(), cmpy);
		nxt = n-1;
		init();
		for (int i = n - 1; i >= 0; i--){
			while (pt[i].y < pt[nxt].y){
				update(pt[nxt].xy, pt[nxt].x);
				nxt--;
			}
			int minx = query(pt[i].xy, mx);
			result[pt[i].idx] = min(result[pt[i].idx], minx - pt[i].x);
		}

		ans = 0;
		for (int i = 0; i < n; i++){
			ans += result[i];
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
