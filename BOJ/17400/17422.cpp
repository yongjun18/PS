#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll tree[270100];
ll dp1[270100];
ll dp2[270100];
ll dp3[270100];

void update_node(int n, int no){
    dp1[no] = tree[no];
    if(2*no <= n)
        dp1[no] += max(dp1[2*no], dp1[2*no+1]);

    dp2[no] = tree[no];
    if(2*no <= n)
        dp2[no] += dp1[2*no] + dp1[2*no+1];

    dp3[no] = dp2[no];
    if(2*no <= n){
        ll tmp = max(dp3[2*no], dp3[2*no+1]);
        dp3[no] = max(dp3[no], tmp);
    }
}
void init(int n, int no){
    if(2*no <= n){
        init(n, 2*no);
        init(n, 2*no+1);
    }
    update_node(n, no);
}
void update(int n, int no, ll val){
    tree[no] = val;
    while(no > 0){
        update_node(n, no);
        no /= 2;
    }
}
int main()
{
    int n, q;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%lld", &tree[i]);
    init(n, 1);
    printf("%lld\n", dp3[1]);

    scanf("%d", &q);
    while(q--){
        int x;
        ll val;
        scanf("%d %lld", &x, &val);
        update(n, x, val);
        printf("%lld\n", dp3[1]);
    }
    return 0;
}
