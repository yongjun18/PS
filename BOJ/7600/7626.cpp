#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 400100;
ll cnt[1600800];
ll tree[1600800];
vector<int> used;

void update(int l, int r, ll val, int no, int nl, int nr){
    if(r <= nl || nr <= l) return;
    else if(l <= nl && nr <= r)
        cnt[no] += val;
    else{
        int mid = (nl+nr)/2;
        update(l, r, val, 2*no, nl, mid);
        update(l, r, val, 2*no+1, mid, nr);
    }
    if(cnt[no] > 0) tree[no] = used[nr]-used[nl];
    else{
        if(nl+1 == nr) tree[no] = 0;
        else tree[no] = tree[2*no] + tree[2*no+1];
    }
}
void update(int l, int r, ll val, int n){ update(l, r, val, 1, 0, n); }


struct Line{
    int x1, x2, y;
    int val;
    bool operator < (const Line& rhs) const{
        return y < rhs.y;
    }
};
vector<Line> lines;

int main()
{
    int n;
    ll ans;

    scanf("%d", &n);
    for(int i=0; i<n; i++){
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
        lines.push_back({x1, x2, y1, 1});
        lines.push_back({x1, x2, y2, -1});
        used.push_back(x1);
        used.push_back(x2);
    }
    sort(lines.begin(), lines.end());

    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());
    for(Line& it : lines){
        it.x1 = lower_bound(used.begin(), used.end(), it.x1) - used.begin();
        it.x2 = lower_bound(used.begin(), used.end(), it.x2) - used.begin();
    }

    ans = 0;
    for(int i=0; i<lines.size(); i++){
        if(i>0 && lines[i-1].y != lines[i].y)
            ans += (lines[i].y - lines[i-1].y) * tree[1];
        update(lines[i].x1, lines[i].x2, lines[i].val, MX);
    }
    printf("%lld\n", ans);
    return 0;
}
