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
vector<int> kmp(const char* a, const char* f) {
    int n = strlen(a), m = strlen(f);
    vector<int> ret;
    vector<int> fail = get_fail(m, f);

    int match = 0;
    for (int last = 0; last < n; last++) {
        while (match > 0 && a[last] != f[match])
            match = fail[match - 1];

        if (a[last] == f[match]) match++;
        if (match == m) {
            ret.push_back(last - match + 1);
            match = fail[match - 1];
        }
    }
    return ret;
}

int n;
char str1[500100];
int len1;
char str2[100][10100];
int len2[100];
int from[100][500100];

void build_from(){
    for(int i=0; i<n; i++){
        for(int j=0; j<len1; j++)
            from[i][j] = -INF;

        vector<int> res = kmp(str1, str2[i]);
        for(int it : res)
            from[i][it+len2[i]-1] = it;

        for(int j=1; j<len1; j++){
            if(from[i][j] < 0)
                from[i][j] = from[i][j-1];
        }
    }
}
int main()
{
    int ans;

    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d %s", &len2[i], str2[i]);
    scanf("%d %s", &len1, str1);

    build_from();
    ans = INF;
    for(int j=0; j<len1; j++){
        int min_from = INF;
        for(int i=0; i<n; i++)
            min_from = min(min_from, from[i][j]);
        ans = min(ans, j-min_from+1);
    }
    printf("%d\n", ans);
    return 0;
}
