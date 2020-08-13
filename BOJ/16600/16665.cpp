#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int get_x(int n){
    int sqrtv = sqrt(n);
    ll div = -1;
    ll ret;

    for(int i=2; i<=sqrtv; i++){
        if(n % i == 0){
            div = i;
            break;
        }
    }
    if(div == -1) div = n;
    ret = div;
    while(n % (ret*div) == 0)
        ret *= div;
    return (int)ret;
}

int main()
{
    int n;
    int x, y, c, d;
    scanf("%d", &n);

    x = get_x(n);

    if(x == n)
        printf("NO\n");
    else{
        printf("YES\n");
        printf("2\n");
        y = n/x;
        for(c=1; c<x; c++){
            if((c*y+1) % x == 0)
                break;
        }
        d = (n-1-c*y)/x;
        printf("%d %d\n", c, x);
        printf("%d %d\n", d, y);
    }
    return 0;
}
