#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> get_fail(int m, const char* f) {
    vector<int> fail(m, 0);
    int match = 0;
    for (int last=1; last<m; last++) {
        while (match > 0 && f[last] != f[match])
            match = fail[match - 1];
        if (f[last] == f[match]) match++;
        fail[last] = match;
    }
    return fail;
}
char str[100100];

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", str);

    if(k >= n) printf("%d\n", n);
    else{
        vector<int> fail = get_fail(n, str);
        int minlen = n-fail.back();

        int ans = 0;
        for(int i=1; minlen*i<n; i++){
            int need;
            int modv = n % (minlen*i);
            if(modv == 0) need = 0;
            else need = (minlen*i) - modv;
            if(need <= k)
                ans = max(ans, minlen*i);
        }
        printf("%d\n", ans);
    }
    return 0;
}
