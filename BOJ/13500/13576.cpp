#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int Z[100100];

void get_Z(int len, char* str){
    int l = -1, r = -1;
    for(int i=1; i<len; i++){
        if(r < i) Z[i] = 0;
        else Z[i] = min(Z[i-l], r-i+1);

        while(i+Z[i] < len && str[i+Z[i]] == str[Z[i]]) Z[i]++;
        if(r < i+Z[i]-1) l = i, r = i+Z[i]-1;
    }
}

char str[100100];
vector< pair<int,int> > ans;

int main()
{
    int len;
    scanf("%s", str);
    len = strlen(str);
    get_Z(len, str);
    Z[0] = len;

    for(int i=len-1; i>=0; i--){
        if(i+Z[i] == len)
            ans.push_back({Z[i], 0});
    }
    for(int i=0; i<len; i++){
        int pos = upper_bound(ans.begin(), ans.end(), make_pair(Z[i], INF)) - ans.begin() - 1;
        if(pos >= 0)
            ans[pos].second++;
    }

    for(int i=(int)ans.size()-1; i>=0; i--)
        ans[i].second += ans[i+1].second;

    printf("%d\n", ans.size());
    for(int i=0; i<ans.size(); i++)
        printf("%d %d\n", ans[i].first, ans[i].second);
    return 0;
}
