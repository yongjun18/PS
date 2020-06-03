#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int init[100100];
int nxt[100100][30];

int main()
{
    int n, k, m;
    scanf("%d %d %d", &n, &k, &m);
    for(int i=1; i<=n; i++)
        scanf("%d", &init[i]);

    for(int i=1; i<=k; i++)
        scanf("%d", &nxt[i][0]);
    for(int j=1; j<30; j++){
        for(int i=1; i<=k; i++)
            nxt[i][j] = nxt[nxt[i][j-1]][j-1];
    }

    for(int i=1; i<=n; i++){
        int now = init[i];
        for(int j=0; j<30; j++){
            if((m-1) & (1<<j))
                now = nxt[now][j];
        }
        printf("%d ", now);
    }
    printf("\n");
    return 0;
}
