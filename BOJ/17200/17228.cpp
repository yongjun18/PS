#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int power = 35;
ll powv[500100];
void init(){
    powv[0] = 1;
    for(int i=1; i<500100; i++)
        powv[i] = (powv[i-1] * power) % MOD;
}

struct Edge{
    int x, y; char c;
};
vector<Edge> adj[500100];
char str[500100];
int len;
ll hval;

char tmp[500100];
int dfs(ll nowh, int now, int depth){
    int ret = 0;
    if(depth >= len && nowh == hval) ret++;

    for(auto it : adj[now]){
        ll nxth = nowh;
        if(depth-len >= 0)
            nxth = ((nxth - tmp[depth-len] * powv[len-1] % MOD) + MOD) % MOD;
        nxth = (nxth * power) % MOD;
        nxth = (nxth + it.c) % MOD;

        tmp[depth] = it.c;
        ret += dfs(nxth, it.y, depth+1);
    }
    return ret;
}

int main()
{
    int n;
    init();
    scanf("%d", &n);
    for(int i=0; i<n-1; i++){
        Edge e;
        scanf("%d %d %c", &e.x, &e.y, &e.c);
        adj[e.x].push_back(e);
    }
    scanf("%s", str);
    len = strlen(str);
    hval = 0;
    for(int i=0; i<len; i++){
        hval = (hval * power) % MOD;
        hval = (hval + str[i]) % MOD;
    }
    printf("%d\n", dfs(0, 1, 0));
    return 0;
}
