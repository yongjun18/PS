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
	vec(){}
	vec(double _x, double _y){ x = _x; y = _y; }

	bool operator < (const vec& rhs) const {
		if (y != rhs.y) return y < rhs.y;
		return x < rhs.x;
	}
	vec operator - (const vec& rhs) const {
		return vec(x - rhs.x, y - rhs.y);
	}
	vec operator + (const vec& rhs) const {
		return vec(x + rhs.x, y + rhs.y);
	}
	vec operator * (double rhs) const {
		return vec(x * rhs, y * rhs);
	}
	double norm() const {
		return hypot(x, y);
	}
	double dot(const vec& rhs) const{
		return x*rhs.x + y*rhs.y;
	}
	vec normalize(){
		double normv = norm();
		return vec(x / normv, y / normv);
	}
};
double ccw(vec a, vec b){
	return a.x * b.y - a.y * b.x;
}

double dist(vec a, vec b, vec c){
	vec v1 = b - a;
	double tmp = ((c - a).dot(b - a)) / (b - a).norm();
	vec h = a + ((b - a).normalize() * tmp);

	if (a < h && h < b) return (h - c).norm();
	if (b < h && h < a) return (h - c).norm();
	return min((a - c).norm(), (b - c).norm());
}


double solve(vector<vec>& p1, vector<vec>& p2){
	double ret = 1e12;

	vec v1, v2;
	int pos2 = -1;
	double now = 1e12;

	for (int i = 0; i < p2.size(); i++){
		v1 = p2[i];
		v2 = p2[(i + 1) % p2.size()];
		double tmp = dist(v1, v2, p1[0]);
		if (now > tmp){
			now = tmp;
			pos2 = i;
		}
	}
	ret = now;

	for (int i = 1; i < p1.size(); i++){
		v1 = p2[pos2];
		v2 = p2[(pos2 + 1) % p2.size()];
		now = dist(v1, v2, p1[i]);

		while (1){
			int pv = (pos2 - 1 + p2.size()) % p2.size();
			double distv = dist(p2[pv], p2[pos2], p1[i]);
			if (distv <= now){
				now = distv;
				pos2 = pv;
				continue;
			}
			break;
		}
		while (1){
			int nx = (pos2 + 1) % p2.size();
			double distv = dist(p2[nx], p2[pos2], p1[i]);
			if (distv <= now){
				now = distv;
				pos2 = nx;
				continue;
			}
			break;
		}
		ret = min(ret, now);
	}
	return ret;
}

vector<vec> pa, pb;

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		double ans;

		scanf("%d %d", &n, &m);
		pa.clear();
		pb.clear();

		for (int i = 0; i < n; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			pa.push_back(vec(x, y));
		}
		for (int i = 0; i < m; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			pb.push_back(vec(x, y));
		}
		ans = min(solve(pa, pb), solve(pb, pa));

		printf("Case #%d\n", test);
		printf("%.12lf\n", ans);
	}

	return 0;
}
