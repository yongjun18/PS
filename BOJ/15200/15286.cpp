#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Point{ int x, y, z; };

int arr[110][110];
vector<Point> ans;
void solve(int mx, int ot1, int ot2){
    for(int i=0; i<max(ot1, ot2); i++)
        arr[min(i, ot1-1)][min(i, ot2-1)] = 1;

    int now = max(ot1, ot2);
    for(int i=0; i<ot1; i++){
        for(int j=0; j<ot2; j++){
            if(now < mx && arr[i][j] == 0){
                arr[i][j] = 1;
                now++;
            }
        }
    }
    for(int i=0; i<ot1; i++){
        for(int j=0; j<ot2; j++){
            if(arr[i][j] == 1)
                ans.push_back({ i, j, 0 });
        }
    }
}

int main()
{
    int a, b, c, maxv;
    scanf("%d %d %d", &a, &b, &c);
    maxv = max({a, b, c});

    if(maxv == a && a <= b*c){
        solve(a, b, c);
    }
    else if(maxv == b && b <= a*c){
        solve(b, a, c);
        for(auto &it : ans) swap(it.y, it.z);
    }
    else if(maxv == c && c <= a*b){
        solve(c, b, a);
        for(auto &it : ans) swap(it.x, it.z);
    }

    if(ans.size() == 0)
        printf("-1\n");
    else{
        printf("%d\n", ans.size());
        for(auto it : ans)
            printf("%d %d %d\n", it.x, it.y, it.z);
    }
    return 0;
}
