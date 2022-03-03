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

const double EPS = 1e-6;

struct vec {
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	double norm() const { return hypot(x, y); }
};

vec center(vec pt1, vec pt2, vec pt3) {
	double tmpx1 = 2 * (pt1.x - pt2.x) * (pt3.y - pt2.y) - 2 * (pt3.x - pt2.x) * (pt1.y - pt2.y);
	double tmpx2 = (pt2.x * pt2.x - pt1.x * pt1.x + pt2.y * pt2.y - pt1.y * pt1.y) * (pt3.y - pt2.y)
		- (pt2.x * pt2.x - pt3.x * pt3.x + pt2.y * pt2.y - pt3.y * pt3.y) * (pt1.y - pt2.y);
	double tmpy1 = 2 * (pt1.y - pt2.y) * (pt3.x - pt2.x) - 2 * (pt3.y - pt2.y) * (pt1.x - pt2.x);
	double tmpy2 = (pt2.y * pt2.y - pt1.y * pt1.y + pt2.x * pt2.x - pt1.x * pt1.x) * (pt3.x - pt2.x)
		- (pt2.y * pt2.y - pt3.y * pt3.y + pt2.x * pt2.x - pt3.x * pt3.x) * (pt1.x - pt2.x);

	if (tmpx1 == 0 || tmpy1 == 0) return pt1;
	return vec(- tmpx2 / tmpx1, - tmpy2 / tmpy1);
}

vector< pair<vec, char> > p;

int compute(vec mid) {
	double maxi = -1;
	double minn = INF;

	for (auto it : p) {
		if (it.second == 'I') {
			maxi = max(maxi, (it.first - mid).norm());
		}
		else {
			minn = min(minn, (it.first - mid).norm());
		}
	}
	return (maxi <= minn);
}

int main()
{
	int n;
	int ok;

	scanf("%d", &n);
	p.resize(n);
	for (auto &it : p) {
		scanf("%lf %lf %c", &it.first.x, &it.first.y, &it.second);
	}

	ok = 0;
	for (int i = 0; !ok && i < n; i++) {
		for (int j = i; !ok && j < n; j++) {
			vec mid = (p[i].first + p[j].first) * 0.5;
			if (compute(mid)) {
				ok = 1;
			}
		}
	}

	for (int i = 0; !ok && i < n; i++) {
		for (int j = i + 1; !ok && j < n; j++) {
			for (int k = j + 1; !ok && k < n; k++) {
				vec mid = center(p[i].first, p[j].first, p[k].first);
				if (compute(mid)) {
					ok = 1;
				}
			}
		}
	}
	printf("%s\n", ok ? "No" : "Yes");
	return 0;
}
