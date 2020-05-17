#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct vec{
    double x, y;
    int num;
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

vector<int> convex_hull(vector<vec>& p){
    vector<int> ret;
    if(p.size() <= 1) return ret;

    sort(p.begin(), p.end());
    s = p[0];
    sort(p.begin()+1, p.end(), cmp);
    ret.push_back(0);
    ret.push_back(1);

    for(int now=2; now<p.size(); now++){
        while(ret.size() >= 2){
            int last1 = *(ret.end() - 1);
            int last2 = *(ret.end() - 2);

            if(ccw(p[last2], p[last1], p[now]) > 0) break;
            ret.pop_back();
        }
        ret.push_back(now);
    }
    return ret;
}

vector<vec> points;
vector<int> ans;

int main()
{
    int n;
    scanf("%d", &n);
    points.resize(n);
    ans.resize(n, 0);

    for(int i=0; i<n; i++){
        scanf("%lf %lf", &points[i].x, &points[i].y);
        points[i].num = i;
    }
    for(int i=1;; i++){
        vector<int> res = convex_hull(points);
        if(res.size() <= 2) break;

        for(int j=(int)res.size()-1; j>=0; j--){
            int pos = res[j];
            ans[points[pos].num] = i;
            swap(points[pos], *(points.rbegin()));
            points.pop_back();
        }
    }
    for(int i=0; i<ans.size(); i++)
        printf("%d ", ans[i]);
    printf("\n");
    return 0;
}
