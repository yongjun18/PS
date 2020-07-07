#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int ti[200100];
int xi[200100];
int yi[200100];
int ans[200100];

struct Node{
    int x, y, num;
    bool operator < (const Node& rhs) const {
        if(x != rhs.x) return x < rhs.x;
        if(y != rhs.y) return y < rhs.y;
        return num < rhs.num;
    }
};
set<Node> arrow;

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d %d %d", &ti[i], &xi[i], &yi[i]);
    memset(ans, -1, sizeof(ans));

    for(int i=n-1; i>=0; i--){
        if(ti[i] == 2)
            arrow.insert({xi[i], yi[i], i});
        else{
            int minnum = INF;
            auto it = arrow.lower_bound({xi[i]-yi[i], 0, 0});
            while(1){
                if(it == arrow.end()) break;
                if(it->x > xi[i]+yi[i]) break;

                ll dx = xi[i]-it->x;
                ll dy = yi[i]-it->y;
                if(dx*dx + dy*dy < (ll)yi[i]*yi[i])
                    minnum = min(minnum, it->num);
                it++;
            }
            if(minnum != INF){
                ans[minnum] = i;
                it--;
                while(it->num != minnum) it--;
                arrow.erase(it);
            }
        }
    }
    for(int i=0; i<n; i++){
        if(ti[i] == 2){
            if(ans[i] == -1) printf("-1\n");
            else printf("%d\n", ans[i]+1);
        }
    }
    return 0;
}
