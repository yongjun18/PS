#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    Trie* fail;
    int cnt, len;
    Trie() : go{}, fail(0), cnt(0), len(0) {}
};
Trie* root;
void trie_insert(const string key){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'a';
        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
        now->cnt++;
        now->len = i+1;
    }
}
void build_fail(){
    root->fail = root;
    queue<Trie*> q;

    for(int i=0; i<26; i++){
        Trie* nxt = root->go[i];
        if(nxt != NULL){
            nxt->fail = root;
            q.push(nxt);
        }
    }
    while(q.size()){
        Trie* now = q.front(); q.pop();
        for(int i=0; i<26; i++){
            Trie* nxt = now->go[i];
            if(nxt != NULL){
                Trie* dest = now->fail;
                while(dest != root && dest->go[i] == NULL)
                    dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                nxt->fail = dest;
                q.push(nxt);
            }
        }
    }
}

ll dp[200100];
char str[200100];

int main()
{
    int n, m;
    scanf("%d", &n);

    root = new Trie();
    for(int i=0; i<n; i++){
        scanf("%s", str);
        trie_insert(str);
    }
    build_fail();

    scanf("%s", str);
    m = strlen(str);
    dp[0] = 1;

    Trie* now = root;
    Trie* tmp;
    for(int i=1; i<=m; i++){
        int nxt = str[i-1]-'a';
        while(now != root && now->go[nxt] == NULL)
            now = now->fail;
        if(now->go[nxt] == NULL)
            break;
        now = now->go[nxt];

        tmp = now;
        while(tmp != root){
            dp[i] += dp[i-tmp->len] * tmp->cnt;
            dp[i] %= MOD;
            tmp = tmp->fail;
        }
    }
    printf("%lld\n", dp[m]);
    return 0;
}
