#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int score[4][10][10];
int dp[2][1<<21];
int num[2][1<<21];

int main()
{
    int n, m, now;
    scanf("%d %d", &n, &m);
    for(int c=0; c<4; c++){
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++)
                scanf("%d", &score[c][i][j]);
        }
    }

    dp[1][0] = 0;
    num[1][0] = 1;
    now = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int mask=0; mask<(1<<(m*2)); mask++)
                dp[now][mask] = num[now][mask] = 0;

            for(int mask=0; mask<(1<<(m*2)); mask++){
                for(int c=0; c<4; c++){
                    int uc = mask / ( 1 << ((m-1)*2) );
                    int lc = mask % (1<<2);
                    if(i > 0 && uc == c) continue;
                    if(j > 0 && lc == c) continue;

                    int nmask = ( (mask<<2) % ( 1<<(m*2) ) )+ c;
                    int nval = dp[now^1][mask] + score[c][i][j];
                    if(dp[now][nmask] < nval){
                        dp[now][nmask] = nval;
                        num[now][nmask] = num[now^1][mask];
                    }
                    else if(dp[now][nmask] == nval){
                        num[now][nmask] += num[now^1][mask];
                        num[now][nmask] %= MOD;
                    }
                }
            }
            now ^= 1;
        }
    }
    int maxdp, maxnum;
    maxdp = maxnum = 0;
    for(int mask = 0; mask<(1<<(m*2)); mask++){
        if(maxdp < dp[now^1][mask]){
            maxdp = dp[now^1][mask];
            maxnum = num[now^1][mask];
        }
        else if(maxdp == dp[now^1][mask]){
            maxnum += num[now^1][mask];
            maxnum %= MOD;
        }
    }
    printf("%d %d\n", maxdp, maxnum);
    return 0;
}
