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

const int MX = 300100;

struct Range {
	int x1, x2, y;
	bool operator < (const Range& rhs) const {
		if (x1 != rhs.x1) return x1 < rhs.x1;
		if (x2 != rhs.x2) return x2 < rhs.x2;
		return y < rhs.y;
	}
};

vector<Range> ranges;

int hole[MX];
int psum[MX];
int highl[MX];
int highr[MX];
stack< pair<int, int> > st;

struct Block {
	int p1, p2, h;
	bool operator < (const Block& rhs) const {
		if (p1 != rhs.p1) return p1 < rhs.p1;
		if (p2 != rhs.p2) return p2 < rhs.p2;
		return h < rhs.h;
	}
	bool operator == (const Block & rhs) const {
		return (p1 == rhs.p1 && p2 == rhs.p2 && h == rhs.h);
	}
};

vector<Block> blocks;

double tim[MX];

int main()
{
	int n, m, k;
	int x1, y1, x2, y2;

	ll remain;
	double inc, ans;

	scanf("%d", &n);

	scanf("%d %d", &x2, &y2);
	ranges.push_back({ -1, x2, y2 });
	for (int i = 1; i + 1 < n; i += 2) {
		scanf("%d %d", &x1, &y1);
		scanf("%d %d", &x2, &y2);
		ranges.push_back({ x1, x2, y2 });
	}
	scanf("%d %d", &x1, &y1);
	ranges.push_back({ x1, x1 + 1, y1 });
	m = ranges.size();

	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		Range tmp = { x1, x2, y2 };
		int pos = lower_bound(ranges.begin(), ranges.end(), tmp) - ranges.begin();
		hole[pos] = 1;
	}
	psum[0] = 0;
	for (int i = 1; i < m; i++) {
		psum[i] = psum[i - 1] + hole[i];
	}

	for (int i = 0; i < m; i++) {
		while (st.size() > 0 && st.top().first >= ranges[i].y)
			st.pop();
		if (st.size() > 0) highl[i] = st.top().second;
		else highl[i] = 0;
		st.push({ ranges[i].y, i });
	}

	for (int i = m - 1; i >= 0; i--) {
		while (st.size() > 0 && st.top().first >= ranges[i].y)
			st.pop();
		if (st.size() > 0) highr[i] = st.top().second;
		else highr[i] = m - 1;
		st.push({ ranges[i].y, i });
	}

	for (int i = 1; i < m - 1; i++) {
		int l = highl[i];
		int r = highr[i];
		int maxv = max(ranges[l].y, ranges[r].y);
		int h = ranges[i].y - maxv;
		blocks.push_back({ l + 1, r - 1, h });
	}
	sort(blocks.begin(), blocks.end());

	remain = 0;
	for (int i = 0; i < blocks.size(); i++) {
		int p1 = blocks[i].p1;
		int p2 = blocks[i].p2;
		int h = blocks[i].h;
		ll x1 = ranges[p1].x1;
		ll x2 = ranges[p2].x2;
		ll sum = (x2 - x1) * h;
		int hcnt = psum[p2] - psum[p1 - 1];

		if (i > 0 && blocks[i - 1] == blocks[i]) continue;

		if (hcnt == 0) {
			remain += sum;
		}
		else {
			double tmp = (double)sum / hcnt;
			tim[p1] += tmp;
			tim[p2 + 1] -= tmp;
		}
	}

	inc = 0;
	for (int i = 0; i < m; i++) {
		inc += tim[i];
		tim[i] = inc;
	}
	ans = 0;
	for (int i = 0; i < m; i++) {
		ans = max(ans, tim[i]);
	}

	printf("%.2lf\n", ans);
	printf("%lld\n", remain);
	return 0;
}
