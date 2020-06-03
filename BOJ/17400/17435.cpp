#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int adj[200100];
int nxt[200100][20];

void build(int m){
    for(int i=1; i<=m; i++)
        nxt[i][0] = adj[i];
    for(int j=1; j<20; j++){
        for(int i=1; i<=m; i++)
            nxt[i][j] = nxt[nxt[i][j-1]][j-1];
    }
}
int query(int go, int x){
    for(int i=0; i<20; i++){
        if(go & (1<<i))
            x = nxt[x][i];
    }
    return x;
}

int main()
{
    int m, q;
    scanf("%d", &m);
    for(int i=1; i<=m; i++)
        scanf("%d", &adj[i]);
    build(m);

    scanf("%d", &q);
    while(q--){
        int go, x;
        scanf("%d %d", &go, &x);
        printf("%d\n", query(go, x));
    }
    return 0;
}
