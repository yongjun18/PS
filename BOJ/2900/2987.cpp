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
	explicit vec(ll x, ll y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	bool operator == (const vec& rhs) { return x == rhs.x && y == rhs.y; }
	bool operator < (const vec& rhs) { if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }

	ll cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};

ll ccw(vec a, vec b) {
	return a.cross(b);
}
ll ccw(vec p, vec a, vec b) {
	return ccw(a - p, b - p);
}

int on_segment(vec a, vec b, vec p) {
	if (ccw(a, b, p) != 0) return 0;
	if (b < a) swap(a, b);
	return a < p && p < b;
}

int in_triangle(vec a, vec b, vec c, vec p) {
	// ccw가 모두 같은 방향
	if (ccw(a, b, p) > 0 && ccw(b, c, p) > 0 && ccw(c, a, p) > 0)
		return 1;
	if (ccw(a, b, p) < 0 && ccw(b, c, p) < 0 && ccw(c, a, p) < 0)
		return 1;

	// 꼭지점 위에 p가 위치
	if (a == p || b == p || c == p) return 1;

	// 변 위에 p가 위치
	if (on_segment(a, b, p)) return 1;
	if (on_segment(a, c, p)) return 1;
	if (on_segment(b, c, p)) return 1;
	return 0;
}

int main()
{
	int n;
	vec a, b, c, p;
	int ans = 0;

	scanf("%lld %lld", &a.x, &a.y);
	scanf("%lld %lld", &b.x, &b.y);
	scanf("%lld %lld", &c.x, &c.y);

	printf("%.1lf\n", abs(ccw(a, b, c)) / 2.0);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld %lld", &p.x, &p.y);
		if (in_triangle(a, b, c, p)) {
			ans++;
		}
	}
	printf("%d\n", ans);

	return 0;
}
