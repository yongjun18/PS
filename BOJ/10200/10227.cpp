#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m, h, w;
int arr[3010][3010];

int chk[3010][3010];
int sum[3010][3010];

void build(){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++)
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + chk[i][j];
    }
}
int query(int x1, int y1, int x2, int y2){
    return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int solve(ll x){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(arr[i][j] <= x) chk[i][j] = 1;
            else chk[i][j] = 0;
        }
    }
    build();
    for(int i=1; i+h-1<=n; i++){
        for(int j=1; j+w-1<=m; j++){
            if(query(i, j, i+h-1, j+w-1) >= (h*w)/2+1)
                return 1;
        }
    }
    return 0;
}
ll binary_search(ll x, ll y) {
    ll lo = x - 1;
    ll hi = y + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main()
{
    scanf("%d %d %d %d", &n, &m, &h, &w);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++)
            scanf("%d", &arr[i][j]);
    }
    printf("%lld\n", binary_search(1, n*m));
    return 0;
}
