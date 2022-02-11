#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;
 
const int MX = 5010;
 
ll fac[MX];
int arr[MX];
 
int cnt[MX];
ll dp[MX];
 
int main()
{
    int t;
 
    scanf("%d", &t);
 
    fac[0] = 1;
    for (int i = 1; i < MX; i++)
        fac[i] = (fac[i - 1] * i) % MOD;
 
    for (int test = 1; test <= t; test++) {
        int n;
        ll ans;
        scanf("%d", &n);
 
        for (int i = 0; i < n + 5; i++) {
            cnt[i] = 0;
            dp[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
            cnt[arr[i]]++;
        }
 
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 0) continue;
            for (int j = n - 1; j >= 0; j--) {
                dp[j + 1] += dp[j] * cnt[i] % MOD;
                dp[j + 1] %= MOD;
            }
        }
 
        ans = fac[n];
        for (int i = 1; i <= n; i++) {
            if (i & 1) {
                ans -= dp[i] * fac[n - i] % MOD;
                ans = (ans + MOD) % MOD;
            }
            else {
                ans += dp[i] * fac[n - i] % MOD;
                ans %= MOD;
            }
        }
        printf("#%d %lld\n", test, ans);
    }
    return 0;
}
