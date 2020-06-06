#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[270100];
int to[270100][101];

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    memset(to, -1, sizeof(to));
    for(int i=0; i<n; i++)
        to[i][arr[i]] = i;

    int ans = 0;
    for(int j=1; j<=100; j++){
        for(int i=0; i<n; i++){
            if(to[i][j] != -1)
                ans = j;
            if(to[i][j] != -1 && to[to[i][j]+1][j] != -1)
                to[i][j+1] = to[to[i][j]+1][j];
        }
    }
    printf("%d\n", ans);
    return 0;
}
