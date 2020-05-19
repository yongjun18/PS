#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct vec{
    double x, y;
    vec operator -(const vec& rhs) const { return {x-rhs.x, y-rhs.y}; }
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
    vector<vec> ret;
    if(p.size() <= 1) return ret;

    sort(p.begin(), p.end());
    s = p[0];
    sort(p.begin()+1, p.end(), cmp);
    ret.push_back(p[0]);
    ret.push_back(p[1]);

    for(int now=2; now<p.size(); now++){
        while(ret.size() >= 2){
            vec last1 = *ret.rbegin();
            vec last2 = *(ret.rbegin()+1);

            if(ccw(last2, last1, p[now]) > 0) break;
            ret.pop_back();
        }
        ret.push_back(p[now]);
    }
    return ret;
}

int n;
vector<vec> pts;
double ternary_search(ll x, ll y){
    ll lo = x-1;
    ll hi = y+1;
    while(lo + 2 < hi){
        ll m1 = (2*lo + hi)/3;
        ll m2 = (lo + 2*hi)/3;
        double a1 = abs(ccw(pts[x], pts[y], pts[m1]));
        double a2 = abs(ccw(pts[x], pts[y], pts[m2]));
        if(a1 >= a2) hi = m2;
        else lo = m1;
    }
    return abs(ccw(pts[x], pts[y], pts[lo+1]));
}

int main()
{
    int t;
    ll ans;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        pts.resize(n);
        for(int i=0; i<n; i++)
            scanf("%lf %lf", &pts[i].x, &pts[i].y);

        pts = convex_hull(pts);
        n = pts.size();
        for(int i=0; i<n; i++)
            pts.push_back(pts[i]);

        ans = 0;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                ll res1 = (ll)ternary_search(i, j);
                ll res2 = (ll)ternary_search(j, i+n);
                ans = max(ans, res1 + res2);
            }
        }
        printf("%lld", ans/2);
        if(ans % 2 == 1) printf(".5");
        printf("\n");
    }
    return 0;
}
