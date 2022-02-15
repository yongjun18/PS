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
const double EPS = 1e-4;

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

double surface(vector<vec>& p) {
	double ret = 0;
	for (int i = 0; i + 1 < p.size(); i++) {
		ret += ccw(p[0], p[i], p[i + 1]) / 2;
	}
	return ret;
}

double gety(vec a, vec b, double x) {
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	double tmp = x - a.x;
	return a.y + dy * tmp / dx;
}

double compute(double x, vector<vec> cvx, double whole) {
	vector<int> idx;
	vector<vec> tmp;
	int i0, i1;
	double part;

	for (int i = 0; i + 1 < cvx.size(); i++) {
		double minx = min(cvx[i].x, cvx[i + 1].x);
		double maxx = max(cvx[i].x, cvx[i + 1].x);
		if (minx <= x && x < maxx) {
			idx.push_back(i);
		}
	}

	i0 = idx[0];
	i1 = idx[1];

	tmp.push_back({ x, gety(cvx[i0], cvx[i0 + 1], x) });
	for (int i = i0 + 1; i <= i1; i++) {
		tmp.push_back(cvx[i]);
	}
	tmp.push_back({ x, gety(cvx[i1], cvx[i1 + 1], x) });
	part = surface(tmp);

	return min(part, whole - part);
}

vector<vec> pts;
double whole;

int main()
{
	int n;
	double minx, maxx;
	double lo, hi;
	
	minx = 1e12;
	maxx = -1e12;

	scanf("%d", &n);
	pts.resize(n);
	for (auto &it : pts) {
		scanf("%lf %lf", &it.x, &it.y);
		minx = min(minx, it.x);
		maxx = max(maxx, it.x);
	}
	pts = convex_hull(pts);
	pts.push_back(pts[0]);
	
	whole = surface(pts);

	lo = minx + EPS;
	hi = maxx - EPS;
	while (hi - lo > EPS) {
		double m1 = (2 * lo + hi) / 3;
		double m2 = (lo + 2 * hi) / 3;
		if (compute(m1, pts, whole) >= compute(m2, pts, whole)) hi = m2;
		else lo = m1;
	}
	printf("%.9lf\n", lo);
	return 0;
}
