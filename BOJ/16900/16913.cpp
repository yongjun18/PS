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

char s[100100];
char t[100100];
vector<int> fail;
int nxt[100100][26];
vector<int> dp[100100];

int main()
{
    int slen, tlen, ans;
    scanf("%s %s", s+1, t);
    slen = strlen(s+1);
    tlen = strlen(t);
    fail = get_fail(tlen, t);
    memset(nxt, -1, sizeof(nxt));

    for(int i=0; i<=slen; i++)
        dp[i].resize(tlen, -1);

    dp[0][0] = 0;
    for(int i=1; i<=slen; i++){
        for(int j=0; j<tlen; j++){
            if(dp[i-1][j] == -1) continue;

            for(char c='a'; c<='z'; c++){
                if(s[i] != '?' && s[i] != c) continue;
                int match = j;
                int cnt = dp[i-1][j];

                if(nxt[match][c-'a'] != -1)
                    match = nxt[match][c-'a'];
                else{
                    int pmatch = match;
                    while(match > 0 && t[match] != c)
                        match = fail[match-1];
                    if(t[match] == c) match++;
                    nxt[pmatch][c-'a'] = match;
                }
                if(match == tlen){
                    cnt++;
                    match = fail[match-1];
                }
                dp[i][match] = max(dp[i][match], cnt);
            }
        }
    }
    ans = 0;
    for(int i=0; i<tlen; i++)
        ans = max(ans, dp[slen][i]);
    printf("%d\n", ans);
    return 0;
}
