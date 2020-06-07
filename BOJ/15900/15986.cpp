#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll arr[400100];
ll gcdv[400100][18];
int to[400100][18];

void build_to0(int n){
    for(int i=0; i<2*n; i++)
        gcdv[i][0] = arr[i];
    for(int j=1; j<18; j++){
        for(int i=0; i<2*n; i++){
            int ot = i+(1<<(j-1));
            if(ot + (1<<(j-1)) <= 2*n)
                gcdv[i][j] = __gcd(gcdv[i][j-1], gcdv[ot][j-1]);
        }
    }
    for(int i=0; i<2*n; i++){
        ll ngv;
        ll gv = -1;
        int now = i;
        for(int j=17; j>=0; j--){
            if(gcdv[now][j] == 0) continue;

            if(gv == -1) ngv = gcdv[now][j];
            else ngv = __gcd(gv, gcdv[now][j]);
            if(ngv != 1){
                gv = ngv;
                now += (1<<j);
            }
        }
        if(now >= 2*n) to[i][0] = INF;
        else to[i][0] = now;
    }
}
void build(int n){
    build_to0(n);
    for(int j=1; j<18; j++){
        for(int i=0; i<2*n; i++){
            if(to[i][j-1]+1 >= 2*n)
                to[i][j] = INF;
            else to[i][j] = to[to[i][j-1]+1][j-1];
        }
    }
}
int query(int x, int y){
    int ans = 0;
    int now = x;
    for(int j=17; j>=0; j--){
        if(to[now][j] <= y){
            now = to[now][j]+1;
            ans += (1<<j);
        }
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%lld", &arr[i]);
        arr[i+n] = arr[i];
    }
    build(n);

    for(int i=0; i<n; i++)
        printf("%d\n", query(i, i+n-1));
    return 0;
}
