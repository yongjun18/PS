#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct vec{
    double x, y;
    vec operator -(const vec& rhs) const { return {x-rhs.x, y-rhs.y}; }
    double norm() const { return hypot(x, y); }
	double dot(const vec& rhs) const { return x * rhs.x + y * rhs.y; }
    bool operator <(const vec &rhs) const {
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
    double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};
double ccw(vec a, vec b){ return a.cross(b); }
double ccw(vec p, vec a, vec b){ return ccw(a-p, b-p); }

vec s;
bool cmp(vec a, vec b){
    if(ccw(a-s, b-s) != 0) return ccw(a-s, b-s) > 0;
    return a < b;
}

vector<vec> convex_hull(vector<vec>& p){
    if(p.size() == 0) return vector<vec>();
    if(p.size() == 1) return vector<vec>(1, p[0]);
    vector<vec> ret;

    sort(p.begin(), p.end());
    s = p[0];
    sort(p.begin()+1, p.end(), cmp);
    ret.push_back(p[0]);
    ret.push_back(p[1]);

    for(int now=2; now<p.size(); now++){
        while(ret.size() >= 2){
            vec last1 = *(ret.end() - 1);
            vec last2 = *(ret.end() - 2);

            if(ccw(last2, last1, p[now]) > 0) break;
            ret.pop_back();
        }
        ret.push_back(p[now]);
    }
    return ret;
}

vector<vec> pts;

int main()
{
    int n, r;
    scanf("%d %d", &n, &r);
    pts.resize(n);
    for(int i=0; i<n; i++)
        scanf("%lf %lf", &pts[i].x, &pts[i].y);
    pts = convex_hull(pts);
    n = pts.size();

    double ans = 0.0;
    double ang = 0.0;
    for(int i=0; i<n; i++)
        ans += (pts[i]-pts[(i+1)%n]).norm();

    for(int i=0; i<n; i++){
        int n1 = (i+1)%n;
        int n2 = (i+2)%n;
        vec a = (pts[n1]-pts[i]);
        vec b = (pts[n2]-pts[n1]);
        ang += acos(a.dot(b) / (a.norm()*b.norm()));
    }
    ans += ang*r;
    printf("%.0lf\n", ans);
    return 0;
}
