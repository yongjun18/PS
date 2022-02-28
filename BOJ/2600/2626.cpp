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

const double PI = 2.0 * acos(0.0);

struct vec{
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	double norm() const { return hypot(x, y); }
	vec normalize() const { double n = norm(); return vec(x / n, y / n); }
};

vector<vec> pt;

int main()
{
	int n;

	vec now;
	double go = 60000.0;
	const double dec = 0.9995;
	
	vec ans;
	double minv;

	scanf("%d", &n);
	pt.resize(n);
	for (auto &it : pt) {
		scanf("%lf %lf", &it.x, &it.y);
	}

	now = pt[0];
	minv = INF;
	for (int i = 0; i < 50000; i++) {
		vec far;
		double dist = -1;
		
		for (auto it : pt) {
			double ndist = (it - now).norm();
			if (dist < ndist) {
				dist = ndist;
				far = it;
			}
		}
		if (minv > dist) {
			minv = dist;
			ans = now;
		}
		now = now + (far - now).normalize() * min(dist, go);
		go *= dec;
	}

	if (abs(round(ans.x * 1000)) < 1.0) ans.x = 0;
	if (abs(round(ans.y * 1000)) < 1.0) ans.y = 0;
	if (abs(round(minv * 1000)) < 1.0) minv = 0;
	printf("%.3lf %.3lf\n", ans.x, ans.y);
	printf("%.3lf\n", minv);
	return 0;
}
