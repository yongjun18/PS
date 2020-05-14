#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n;
char str[1000100];
int SA[1000100], tmp[1000100];
int pos[1000100];
int gap;
int LCP[1000100];

bool cmp(int i, int j) {
    if (pos[i] != pos[j]) return pos[i] < pos[j];
    i += gap; j += gap;
    if (i < n && j < n) return pos[i] < pos[j];
    else return i > j;
}
void build_SA() {
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

int m;
int who[1000100];
int solve(ll x){
    int lo=0, hi, bit;

    while(lo < n){
        hi = lo;
        bit = (1<<who[SA[hi]]);
        while(hi+1 < n && LCP[hi] >= x){
            hi++;
            bit |= (1<<who[SA[hi]]);
        }
        if(bit == (1<<m)-1) return 1;
        lo = hi+1;
    }
    return 0;
}
ll binary_search(ll x, ll y) {
    ll lo = x - 1;
    ll hi = y + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(mid)) lo = mid;
        else hi = mid;
    }
    return lo;
}

int main()
{
    scanf("%d", &m);
    n = 0;
    for(int i=0; i<m; i++){
        scanf("%s", str+n);
        int len = strlen(str+n);
        for(int j=n; j<n+len; j++) who[j] = i;
        n += len;
    }
    build_SA();
    build_LCP();
    printf("%lld\n", binary_search(1, 100100));
    return 0;
}
