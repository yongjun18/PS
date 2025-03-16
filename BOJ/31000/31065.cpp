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

const ll MINV = 0;
const ll MAXV = 2e9;

struct Plant {
    ll height, a;
    int order;
    bool operator <(const Plant& rhs) const {
        return order < rhs.order;
    }
};
vector<Plant> plants;

int main() 
{
    int t;
    int n;
    ll lo, hi;
    
    scanf("%d", &t);
    for(int test=0; test<t; test++){
        scanf("%d", &n);
        plants.resize(n);
        for(int i=0; i<n; i++){
            scanf("%lld", &plants[i].height);
        }
        for(int i=0; i<n; i++){
            scanf("%lld", &plants[i].a);
        }
        for(int i=0; i<n; i++){
            scanf("%d", &plants[i].order);
        }
        sort(plants.begin(), plants.end());

        hi = MAXV;
        lo = MINV;
        for(int i=1; i<n; i++){
            if(plants[i-1].a == plants[i].a){
                if(plants[i-1].height <= plants[i].height){
                    lo = MAXV+1;
                }
            }
            else if(plants[i-1].a > plants[i].a){
                ll val1 = plants[i].height-plants[i-1].height;
                ll val2 = plants[i-1].a-plants[i].a;
                ll newVal = val1/val2;
                if(val1 >= 0) {
                    newVal += 1;
                }
                lo = max(lo, newVal);
            }
            else {
                ll val1 = plants[i].height-plants[i-1].height;
                ll val2 = plants[i-1].a-plants[i].a;
                ll newVal = val1/val2;
                if(val1 % val2 == 0 && newVal >= 0) {
                    newVal -= 1;
                }
                hi = min(hi, newVal);
            }
        }
        if(lo <= hi) {
            printf("%lld\n", lo);
        }
        else {
            printf("-1\n");
        }
    }
    
    return 0;
}
