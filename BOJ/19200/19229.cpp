#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char input[1000100];
char ans[1005][1005];

int main()
{
    int n, l, k;
    int from;
    int x, y, now;
    scanf("%d %d %d", &n, &l, &k);
    scanf("%s", input);
    sort(input, input + n*l);

    now = from = 0;
    x = -1;
    y = 0;
    while(1){
        if(x == k-1 && y == l-1) break;

        if(x == k-1){
            while(ans[from][y] != ans[k-1][y]) from++;
            x = from;
            y = y+1;
        }
        else x = x+1;
        ans[x][y] = input[now++];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<l; j++){
            if(ans[i][j] == 0)
                ans[i][j] = input[now++];
        }
    }
    for(int i=0; i<n; i++)
        printf("%s\n", ans[i]);
    return 0;
}
