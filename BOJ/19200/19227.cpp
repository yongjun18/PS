#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[2000100];
vector<int> app;

int main()
{
    int t, n;
    int minv;
    scanf("%d", &t);

    while(t--){
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            arr[i] = 0;
        app.clear();

        for(int i=0; i<n; i++){
            int color;
            scanf("%d", &color);
            arr[color]++;
        }
        for(int i=1; i<=n; i++){
            if(arr[i] > 0)
                app.push_back(arr[i]);
        }
        sort(app.begin(), app.end());

        minv = INF;
        for(int s=1; s<=app[0]+1; s++){
            int sum = 0;
            for(int i=0; i<app.size(); i++){
                int cnt = (app[i]+s-1)/s;
                if(app[i] < cnt * (s-1)){
                    sum = INF;
                    break;
                }
                sum += cnt;
            }
            minv = min(minv, sum);
        }
        printf("%d\n", minv);
    }
    return 0;
}
