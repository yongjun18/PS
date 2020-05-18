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
vector<vec> pts;

int main()
{
    int n, x, y;
    int rev = 0;
    scanf("%d", &n);
    pts.resize(n);
    for(int i=0; i<n; i++)
        scanf("%lf %lf", &pts[i].x, &pts[i].y);
    pts.push_back(pts[0]);

    scanf("%d %d", &x, &y);
    if(x == 0) x = n;
    if(y == 0) y = n;
    if(x > y) {
        swap(x, y);
        rev = 1;
    }

    vector<int> ans;
    ans.push_back(y);
    ans.push_back(y-1);

    for(int now=y-2; now>=x; now--){
        while(ans.size() >= 2){
            int last1 = *(ans.end()-1);
            int last2 = *(ans.end()-2);

            if(ccw(pts[last2], pts[last1], pts[now]) > 0) break;
            ans.pop_back();
        }
        ans.push_back(now);
    }
    if(rev) reverse(ans.begin(), ans.end());
    ans[0] %= n;
    ans.back() %= n;

    printf("%d\n", ans.size());
    for(int i=(int)ans.size()-1; i>=0; i--)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
