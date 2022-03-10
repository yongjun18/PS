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
	double x, y;
	vec operator -(const vec &rhs) const { return { x - rhs.x, y - rhs.y }; }
	bool operator <(const vec &rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};
double ccw(vec a, vec b) { return a.cross(b); }
double ccw(vec p, vec a, vec b) { return ccw(a - p, b - p); }

vec s;
bool cmp(vec a, vec b) {
	if (ccw(a - s, b - s) != 0) return ccw(a - s, b - s) > 0;
	return a < b;
}

vector<vec> convex_hull(vector<vec>& p) {
	if (p.size() == 0) return vector<vec>();
	if (p.size() == 1) return vector<vec>(1, p[0]);
	vector<vec> ret;

	sort(p.begin(), p.end());
	s = p[0];
	sort(p.begin() + 1, p.end(), cmp);
	ret.push_back(p[0]);
	ret.push_back(p[1]);

	for (int now = 2; now < p.size(); now++) {
		while (ret.size() >= 2) {
			vec last1 = *(ret.end() - 1);
			vec last2 = *(ret.end() - 2);

			if (ccw(last2, last1, p[now]) > 0) break;
			ret.pop_back();
		}
		ret.push_back(p[now]);
	}
	return ret;
}

vector<vec> pts;

int main()
{
	int n;
	double ans;

	scanf("%d", &n);
	pts.resize(n);
	for (auto &it : pts) {
		scanf("%lf %lf", &it.x, &it.y);
	}

	pts = convex_hull(pts);
	ans = 0;
	pts.push_back(pts[0]);
	for (int i = 1; i < pts.size(); i++) {
		double dx = pts[i].x - pts[i - 1].x;
		double dy = pts[i].y - pts[i - 1].y;
		ans += hypot(dx, dy);
	}
	printf("%.2lf\n", ans);
	return 0;
}
