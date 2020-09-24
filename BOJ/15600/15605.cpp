#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const double PI = 2.0 * acos(0.0);

struct vec {
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }
	bool operator == (const vec& rhs) { return x == rhs.x && y == rhs.y; }
	bool operator < (const vec& rhs) { if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};
double ccw(vec p, vec a, vec b) {
	return (a - p).cross(b - p);
}

vector<vec> pts;
vector<vec> gyl[10];

int cover(double x, int k){
	int ret = 0;

	for(vec it : pts){
		int ok = 1;
		for(int i=0; i<k; i++){
			if(ccw(gyl[k][i]*x, gyl[k][(i+1)%k]*x, it) <= 0){
				ok = 0;
				break;
			}
		}
		ret += ok;
	}
	return ret;
}

double parametric_search(double x, double y, int k, int inner){
	for(int i=0; i<60; i++){
		double mid = (x+y)/2;
		int cnt = cover(mid, k);

		if(inner == 1){
			if(cnt == 0) x = mid;
			else y = mid;
		}
		else{
			if(cnt == pts.size()) y = mid;
			else x = mid;
		}
	}
	return x;
}

int main()
{
	int n;
	int ansk = 0;
	double ansv = 0;

	scanf("%d", &n);
	pts.resize(n);
	for(int i=0; i<n; i++)
		scanf("%lf %lf", &pts[i].x, &pts[i].y);

	for(int k=3; k<=8; k++){
		double angle = 2*PI / k;
		for(int i=0; i<k; i++){
			gyl[k].push_back(vec( cos(angle*i), sin(angle*i) ));
		}
	}

	for(int k=3; k<=8; k++){
		double inner = parametric_search(0.1, 1e9, k, 1);
		double outer = parametric_search(0.1, 1e9, k, 0);

		double score = (inner*inner) / (outer*outer);
		if(ansv < score){
			ansv = score;
			ansk = k;
		}
	}
	printf("%d %.9lf\n", ansk, ansv);
	return 0;
}
