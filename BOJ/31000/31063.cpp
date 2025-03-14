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

ll cow[200100];
int candy[200100];

int main() 
{
    int n, m;

    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++) {
        scanf("%lld", &cow[i]);
    }
    for(int j=0; j<m; j++) {
        scanf("%d", &candy[j]);
    }

    for(int j=0; j<m; j++) {
        int bottom = 0;
        for(int i=0; i<n; i++) {
            if(bottom >= candy[j]) {
                break;
            }
            ll eat = max(0LL, min((ll)candy[j], cow[i]) - bottom);
            bottom += eat;
            cow[i] += eat;
        }
    }
    for(int i=0; i<n; i++){
        printf("%lld\n", cow[i]);
    }
    return 0;
}
