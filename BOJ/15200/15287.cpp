#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[1010];
int cnt[1010];
vector<int> ans;

int main()
{
    int n, unicorn, ok;

    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &arr[i]);

    ok = 1;
    unicorn = 0;
    for(int i=0; i<n; i++){
        if(arr[i] > 0) cnt[arr[i]]++;
        if(arr[i] == 0) unicorn++;
        if(arr[i] < 0){
            int need = -arr[i];
            if(cnt[need] > 0) cnt[need]--;
            else if(unicorn == 0){
                ok = 0;
                break;
            }
            else{
                unicorn--;
                ans.push_back(need);
            }
        }
    }
    while(unicorn > 0){
        ans.push_back(1);
        unicorn--;
    }
    if(ok == 1){
        printf("Yes\n");
        for(int it : ans) printf("%d ", it);
        printf("\n");
    }
    else printf("No\n");
    return 0;
}
