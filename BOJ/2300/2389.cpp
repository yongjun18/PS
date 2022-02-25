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

struct vec{
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	double norm() const { return hypot(x, y); }
};

// https://m.blog.naver.com/hileejaeho/221751241141
vec center(vec pt1, vec pt2, vec pt3){
	double A = pt2.x - pt1.x;
	double B = pt2.y - pt1.y;
	double C = pt3.x - pt1.x;
	double D = pt3.y - pt1.y;
	double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
	double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
	double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));
	if (G == 0) return pt1;

	vec ret;
	ret.x = (D * E - B * F) / G;
	ret.y = (A * F - C * E) / G;

	return ret;
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
