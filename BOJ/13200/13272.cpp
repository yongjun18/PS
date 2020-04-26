#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n;
char str[500100];
int SA[500100], tmp[500100];
int pos[500100];
int gap;
int LCP[500100];

bool cmp(int i, int j) {
    if (pos[i] != pos[j]) return pos[i] < pos[j];
    i += gap; j += gap;
    if (i < n && j < n) return pos[i] < pos[j];
    else return i > j;
}
void build_SA() {
    n = strlen(str);
    for (int i = 0; i < n; i++) {
        SA[i] = i;
        pos[i] = str[i];
    }
    for (gap = 1;; gap *= 2) {
        sort(SA, SA + n, cmp);
        tmp[0] = 0;
        for (int i = 0; i < n - 1; i++)
            tmp[i + 1] = tmp[i] + cmp(SA[i], SA[i + 1]);
        for (int i = 0; i < n; i++)
            pos[SA[i]] = tmp[i];
        if (tmp[n - 1] == n - 1) break;
    }
}
void build_LCP() {
    int match = 0;
    for (int i = 0; i < n; i++) {
        if (match) match--;
        if (pos[i] == n - 1) continue;

        int j = SA[pos[i] + 1];
        while (str[i + match] == str[j + match]) match++;
        LCP[pos[i]] = match;
    }
}

int a, b, c, d;
int to[500100];
void build_to(){
    memset(to, -1, sizeof(to));
    int x = 0;
    int y = 0;
    int num = 0;
    int spc = 0;
    int big = 0;

    while(y < n){
        if('0' <= str[y] && str[y] <= '9') num++;
        else if('A' <= str[y] && str[y] <= 'Z') big++;
        else if(str[y] < 'a' || 'z' < str[y]) spc++;
        y++;
        if(y-x < a || num < b || spc < c || big < d) continue;
        to[x] = y-1;

        while(x < n){
            if('0' <= str[x] && str[x] <= '9') num--;
            else if('A' <= str[x] && str[x] <= 'Z') big--;
            else if(str[x] < 'a' || 'z' < str[x]) spc--;
            x++;
            if(y-x < a || num < b || spc < c || big < d) break;
            to[x] = y-1;
        }
    }
}

ll total;
int cnt[500100];
void build_cnt(){
    total = 0;
    for(int i=0; i<n; i++){
        if(to[SA[i]] == -1)
            cnt[i] = 0;
        else cnt[i] = n - to[SA[i]];
    }
    for(int i=0; i<n-1; i++){
        if(to[SA[i]] != -1)
            cnt[i+1] -= max(0, SA[i]+LCP[i] - to[SA[i]]);
    }
    for(int i=0; i<n; i++)
        total += cnt[i];
}

void print_ans(){
    ll pass = 0;
    ll mid = (total+1)/2;

    for(int i=0; i<n; i++){
        if(pass + cnt[i] >= mid){
            ll more = mid - pass;
            int base = to[SA[i]];
            if(i > 0 && to[SA[i-1]] != -1)
                base += max(0, SA[i-1]+LCP[i-1] - to[SA[i-1]]);

            for(int j=SA[i]; j<base; j++)
                printf("%c", str[j]);
            for(int j=base; j<base+more; j++)
                printf("%c", str[j]);
            printf("\n");
            break;
        }
        pass += cnt[i];
    }
}

int main()
{
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    scanf("%s", str);
    build_SA();
    build_LCP();
    build_to();
    build_cnt();

    print_ans();
    return 0;
}
