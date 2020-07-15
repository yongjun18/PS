#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int fail[500100];
int nxt[500100][26];

struct Edge{ int u, v; char c; };
vector<Edge> adj[500100];
char str[500100];
int len;
int mat[500100];

void get_fail(int m, const char* f) {
    int match = 0;
    for (int last=1; last<m; last++) {
        while (match > 0 && f[last] != f[match])
            match = fail[match - 1];
        if (f[last] == f[match]) match++;
        fail[last] = match;
    }
}
int get_nxt(int match, char c, const char* f){
    int& ret = nxt[match][c-'a'];
    if(ret != -1) return ret;

    while(match > 0 && c != f[match])
        match = fail[match-1];
    if(c == f[match]) match++;
    return ret = match;
}
int dfs(int now){
    int ret = 0;
    if(mat[now] == len) ret++;

    for(Edge e : adj[now]){
        mat[e.v] = get_nxt(mat[now], e.c, str);
        ret += dfs(e.v);
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
    memset(nxt, -1, sizeof(nxt));
    get_fail(len, str);

    mat[1] = 0;
    printf("%d\n", dfs(1));
    return 0;
}
