#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Hash{
    static const int MX = 500100;
    ll power;
    ll powv[MX];

    Hash(int p){
        power = p;
        powv[0] = 1;
        for(int i=1; i<MX; i++)
            powv[i] = (powv[i-1] * power) % MOD;
    }
    ll next(int siz, ll phash, ll delv, ll newv){
        ll ret = phash;
        ret = ((ret - delv * powv[siz-1] % MOD) + MOD) % MOD;
        ret = (ret * power) % MOD;
        ret = (ret + newv) % MOD;
        return ret;
    }
};
Hash hsh1(13), hsh2(7);;

struct Edge{
    int u, v;
    char c;
};
vector<Edge> adj[500100];
char str[500100];
int len;
ll hashs1, hashs2;
ll hashv1[500100];
ll hashv2[500100];

char st[500100];
int dfs(int now, int depth){
    int ret = 0;
    if(depth >= len-1){
        if(hashv1[now] == hashs1 && hashv2[now] == hashs2)
            ret++;
    }
    for(Edge e : adj[now]){
        char pv;
        if(depth+1-len >= 0) pv = st[depth+1-len];
        else pv = 0;

        st[depth+1] = e.c;
        hashv1[e.v] = hsh1.next(len, hashv1[now], pv, e.c);
        hashv2[e.v] = hsh2.next(len, hashv2[now], pv, e.c);
        ret += dfs(e.v, depth+1);
    }
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n-1; i++){
        Edge e;
        scanf("%d %d %c", &e.u, &e.v, &e.c);
        adj[e.u].push_back(e);
    }
    scanf("%s", str);

    len = strlen(str);
    hashs1 = hashs2 = 0;
    for(int i=0; i<len; i++){
        hashs1 = hsh1.next(len, hashs1, 0, str[i]);
        hashs2 = hsh2.next(len, hashs2, 0, str[i]);
    }
    printf("%d\n", dfs(1, -1));
    return 0;
}
