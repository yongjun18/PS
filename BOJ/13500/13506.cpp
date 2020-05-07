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
int can_mid[1000100];
int can_end[1000100];

int main()
{
    int len;
    scanf("%s", str);
    len = strlen(str);
    get_Z(len, str);

    for(int i=1; i<len; i++){
        int tmp = min(Z[i], len-i-1);
        can_mid[tmp] = 1;
    }
    for(int i=len; i>=0; i--){
        if(can_mid[i+1])
            can_mid[i] = 1;
    }
    for(int i=1; i<len; i++){
        if(i+Z[i] == len)
            can_end[Z[i]] = 1;
    }

    int ans = -1;
    for(int i=1; i<=len; i++){
        if(can_mid[i] && can_end[i])
            ans = i;
    }

    if(ans == -1) printf("-1\n");
    for(int i=0; i<ans; i++)
        printf("%c", str[i]);
    printf("\n");
    return 0;
}
