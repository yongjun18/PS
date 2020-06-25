#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char str[101];
int dp[101][101];

int memo(int x, int y){
    if(x == y) return 1;
    int &ret = dp[x][y];
    if(ret != 0) return ret;
    if(str[x] == str[y]) return ret = memo(x, y-1);

    ret = INF;
    for(int i=x; i<=y-1; i++)
        ret = min(ret, memo(x, i) + memo(i+1, y));
    return ret;
}
int main()
{
    int n;
    scanf("%d", &n);
    scanf("%s", str);
    printf("%d\n", memo(0, n-1));
    return 0;
}
