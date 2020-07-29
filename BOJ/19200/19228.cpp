#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int last;
int cnt[25];

ll comb[25][25];
ll nCk(int n, int k){
    if(n<0 || k<0 || n<k) return 0;
    if(comb[n][k] != -1) return comb[n][k];

    if(k==0 || n==k) return comb[n][k] = 1;
    return comb[n][k] = nCk(n-1, k-1) + nCk(n-1, k);
}
ll compute(){
    ll res = 1;
    int sum = 0;
    for(int i=24; i>0; i--){
        if(cnt[i] == 0) continue;
        int n = last-sum-i;
        res *= nCk(n, cnt[i]);
        sum += cnt[i];
    }
    return res;
}
ll compute_last0(){
    if(cnt[0] == 0) return 0;
    ll res = 1;
    int sum = 1;
    for(int i=24; i>0; i--){
        if(cnt[i] == 0) continue;
        int n = last-sum-i;
        res *= nCk(n, cnt[i]);
        sum += cnt[i];
    }
    return res;
}

int main()
{
    int t;
    scanf("%d", &t);
    memset(comb, -1, sizeof(comb));

    while(t--){
        ll k;
        scanf("%lld", &k);
        memset(cnt, 0, sizeof(cnt));

        for(int i=2; k>0; i++){
            cnt[k%i]++;
            k/=i;
            last=i;
        }
        ll res1 = compute();
        ll res2 = compute_last0();
        printf("%lld\n", res1 - res2 - 1);
    }
    return 0;
}
