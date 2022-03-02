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

	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
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

vector<vec> p;

double compute(vec mid) {
	double maxv = 0;
	for (vec it : p) {
		maxv = max(maxv, (it - mid).norm());
	}
	return maxv;
}

int main()
{
	int n;
	double ansr;
	vec ans;

	scanf("%d", &n);
	p.resize(n);
	for (auto &it : p) {
		scanf("%lf %lf", &it.x, &it.y);
	}

	ansr = INF;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			vec mid((p[i].x + p[j].x) / 2, (p[i].y + p[j].y) / 2);
			double res = compute(mid);
			if (ansr > res) {
				ansr = res;
				ans = mid;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			for (int k = j + 1; k < n; k++) {
				vec mid = center(p[i], p[j], p[k]);
				double res = compute(mid);
				if (ansr > res) {
					ansr = res;
					ans = mid;
				}
			}
		}
	}
	printf("%.6lf %.6lf %.6lf\n", ans.x, ans.y, ansr);
	return 0;
}
