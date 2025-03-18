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

char str[300100];
vector<int> bundles;

int main() 
{
    int n;
    int lo, hi, dayVal;
    int len, ans;

    scanf("%d", &n);
    scanf("%s", str);
    lo = 0;
    hi = -1;
    dayVal = INF;

    while(true) {
        while(lo < n && str[lo] == '0') {
            lo += 1;
        }
        if(lo >= n) {
            break;
        }
        hi = lo;
        while(hi+1 < n && str[hi+1] == '1') {
            hi += 1;
        }
        len = hi-lo+1;
        bundles.push_back(len);

        if(lo == 0 || hi == n-1) {
            dayVal = min(dayVal, len-1);
        }
        else {
            dayVal = min(dayVal, (len+1)/2 - 1);
        }
        lo = hi+1;
    }
    ans = 0;
    for(int it: bundles) {
        ans += (it + 2*dayVal) / (2*dayVal + 1);
    }
    printf("%d\n", ans);
    return 0;
}
