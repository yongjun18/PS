#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int Z[1000100];

void get_Z(int len, char* str){
    int l = -1, r = -1;
    for(int i=1; i<len; i++){
        if(r < i) Z[i] = 0;
        else Z[i] = min(Z[i-l], r-i+1);

        while(i+Z[i] < len && str[i+Z[i]] == str[Z[i]]) Z[i]++;
        if(r < i+Z[i]-1) l = i, r = i+Z[i]-1;
    }
}

char str[1000100];

int main()
{
    int len, m;
    scanf("%s", str);
    len = strlen(str);
    reverse(str, str+len);
    get_Z(len, str);

    scanf("%d", &m);
    while(m--){
        int x;
        scanf("%d", &x);
        if(x == len) printf("%d\n", len);
        else printf("%d\n", Z[len-x]);
    }
    return 0;
}
