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

struct vec {
	ll x, y;
	vec operator -(const vec& rhs) const { return { x - rhs.x, y - rhs.y }; }
	bool operator <(const vec &rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
	ll cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
	ll distv() const { return x * x + y * y; }
};

ll ccw(vec a, vec b) { return a.cross(b); }
ll ccw(vec p, vec a, vec b) { return ccw(a - p, b - p); }
vec s;
bool cmp(vec a, vec b) {
	if (ccw(a - s, b - s) != 0) return ccw(a - s, b - s) > 0;
	return a < b;
}

vector<int> convex_hull(vector<vec>& p) {
	sort(p.begin(), p.end());
	s = p[0];
	sort(p.begin() + 1, p.end(), cmp);

	vector<int> ret;
	ret.push_back(0);
	ret.push_back(1);

	for (int now = 2; now < p.size(); now++) {
		while (ret.size() >= 2) {
			int last1 = *(ret.end() - 1);
			int last2 = *(ret.end() - 2);
			if (ccw(p[last2], p[last1], p[now]) > 0) break;
			ret.pop_back();
		}
		ret.push_back(now);
	}
	return ret;
}

vec ans1, ans2;
ll rotating_calipers(vector<vec>& p) {
	vector<int> tmp = convex_hull(p);
	vector<vec> cx;
	for (int now : tmp) cx.push_back(p[now]);

	int p1, p2;
	ll maxv;

	p1 = 0; p2 = 1;
	maxv = (cx[p1] - cx[p2]).distv();
	ans1 = cx[p1];
	ans2 = cx[p2];

	for (int t = 0; t < cx.size() * 2; t++) {
		int np1 = (p1 + 1) % cx.size();
		int np2 = (p2 + 1) % cx.size();
		ll tmp = ccw(cx[np1] - cx[p1], cx[p2] - cx[np2]);

		if (tmp > 0) p1 = np1;
		if (tmp < 0) p2 = np2;
		if (tmp == 0) { p1 = np1; p2 = np2; }

		ll nowv = (cx[p1] - cx[p2]).distv();
		if (maxv < nowv) {
			maxv = nowv;
			ans1 = cx[p1];
			ans2 = cx[p2];
		}
	}
	return maxv;
}

vector<vec> pts;

int main()
{
	int c;

	scanf("%d", &c);
	pts.resize(c);
	for (auto &it : pts) {
		scanf("%lld %lld", &it.x, &it.y);
	}

	printf("%lld\n", rotating_calipers(pts));
	return 0;
}
