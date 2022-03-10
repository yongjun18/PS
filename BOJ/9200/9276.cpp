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

	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	vec operator -(const vec& rhs) const { return vec(x - rhs.x, y - rhs.y); }
	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	bool operator <(const vec &rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
	double norm() const { return hypot(x, y); }
	vec normalize() const { double n = norm(); return vec(x / n, y / n); }
	double dot(const vec& rhs) const { return x * rhs.x + y * rhs.y; }
	vec project(const vec& rhs) const {
		vec r = rhs.normalize();
		return r * r.dot(*this);
	}
};

vec perpendicular_foot(vec p, vec a, vec b) {
	return a + (p - a).project(b - a);
}
double point_to_line(vec p, vec a, vec b) {
	return (p - perpendicular_foot(p, a, b)).norm();
}

double ccw(vec a, vec b) { return a.cross(b); }
double ccw(vec p, vec a, vec b) { return ccw(a - p, b - p); }
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

double compute(vector<vec>& p, int pcnt, int a, int b, int c) {
	vec pf = perpendicular_foot(p[c], p[a], p[b]);
	double ret = (p[c] - pf).norm() * 2;
	double lv, rv;
	int cl, cr;
	int lo, hi;

	cl = c;
	cr = c + pcnt;
	if (b < cl) {
		a += pcnt;
		b += pcnt;
	}

	lo = b - 1;
	hi = cr + 1;
	while (lo + 2 < hi) {
		int m1 = (2 * lo + hi) / 3;
		int m2 = (lo + 2 * hi) / 3;

		double dv1 = point_to_line(p[m1], pf, p[cr]);
		if (ccw(pf, p[cr], p[m1]) >= 0) dv1 *= -1;
		double dv2 = point_to_line(p[m2], pf, p[cr]);
		if (ccw(pf, p[cr], p[m2]) >= 0) dv2 *= -1;

		if (dv1 >= dv2) hi = m2;
		else lo = m1;
	}
	rv = point_to_line(p[lo + 1], pf, p[cr]);

	lo = cl - 1;
	hi = a + 1;
	while (lo + 2 < hi) {
		int m1 = (2 * lo + hi) / 3;
		int m2 = (lo + 2 * hi) / 3;

		double dv1 = point_to_line(p[m1], pf, p[cr]);
		if (ccw(pf, p[cr], p[m1]) <= 0) dv1 *= -1;
		double dv2 = point_to_line(p[m2], pf, p[cr]);
		if (ccw(pf, p[cr], p[m2]) <= 0) dv2 *= -1;

		if (dv1 >= dv2) hi = m2;
		else lo = m1;
	}
	lv = point_to_line(p[lo + 1], pf, p[cr]);

	ret += (lv + rv) * 2;
	return ret;
}

double rotating_calipers(vector<vec>& p) {
	vector<int> tmp = convex_hull(p);
	int pcnt;
	vector<vec> cx;
	for (int now : tmp) cx.push_back(p[now]);
	pcnt = cx.size();
	for (int i = 0; i < pcnt; i++) {
		cx.push_back(cx[i]);
	}

	int p1, p2;
	double minv;
	p1 = 0; p2 = 1;
	minv = INF;

	for (int t = 0; t < pcnt * 2; t++) {
		int np1 = (p1 + 1) % pcnt;
		int np2 = (p2 + 1) % pcnt;
		double tmp = ccw(cx[np1] - cx[p1], cx[p2] - cx[np2]);

		if (tmp > 0) {
			if (t >= pcnt)
				minv = min(minv, compute(cx, pcnt, p1, p1 + 1, p2));
			p1 = np1;
		}
		else if (tmp < 0) {
			if (t >= pcnt)
				minv = min(minv, compute(cx, pcnt, p2, p2 + 1, p1));
			p2 = np2;
		}
		else {
			if (t >= pcnt)
				minv = min(minv, compute(cx, pcnt, p2, p2 + 1, p1));
			p1 = np1; p2 = np2;
		}
	}
	return minv;
}

vector<vec> pts;

int main()
{
	int n;

	while (scanf("%d", &n) > 0) {
		pts.resize(n);
		for (auto &it : pts) {
			scanf("%lf %lf", &it.x, &it.y);
		}
		printf("%.9lf\n", rotating_calipers(pts));
	}
	return 0;
}
