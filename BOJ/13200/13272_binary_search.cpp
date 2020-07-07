#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, a, b, c, d;
char str[500001];
int SA[500000], tmp[500000];
int pos[500000];
int gap;
int LCP[500000];

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

int len[500100];
int num[500100];
int spc[500100];
int big[500100];

void build_sum(){
    for(int i=0; i<n; i++){
        if(i > 0){
            num[i] = num[i-1];
            spc[i] = spc[i-1];
            big[i] = big[i-1];
        }
        if('a' <= str[i] && str[i] <= 'z');
        else if('A' <= str[i] && str[i] <= 'Z') big[i]++;
        else if('0' <= str[i] && str[i] <= '9') num[i]++;
        else spc[i]++;
        len[i] = i+1;
    }
}
int solve(int bg, ll x){
    int aval = len[x];
    int bval = num[x];
    int cval = spc[x];
    int dval = big[x];
    if(bg){
        aval -= len[bg-1];
        bval -= num[bg-1];
        cval -= spc[bg-1];
        dval -= big[bg-1];
    }
    return (aval >= a && bval >= b && cval >= c && dval >= d);
}
ll bin_search(int bg, ll x, ll y) {
    ll lo = x - 1;
    ll hi = y + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(bg, mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}
ll get_total(){
    ll ret = 0;
    for(int i=0; i<n; i++){
        int bg = SA[i];
        ll x = bg;
        if(i) x += LCP[i-1];
        x = bin_search(bg, x, n-1);
        ret += n - x;
    }
    return ret;
}
void print_kth(ll k){
    ll tot = 0;
    for(int i=0; i<n; i++){
        int bg = SA[i];
        ll x = bg;
        if(i) x += LCP[i-1];
        x = bin_search(bg, x, n-1);
        ll nxt = tot + n - x;
        if(nxt >= k){
            for(int j=bg; j<x+k-tot; j++)
                printf("%c", str[j]);
            return;
        }
        tot = nxt;
    }
}
int main()
{
    ll total;
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
    scanf("%s", str);
    build_SA();
    build_LCP();
    build_sum();

    total = get_total();
    print_kth((total+1)/2);
    return 0;
}
