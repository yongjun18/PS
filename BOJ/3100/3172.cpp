#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    int cnt, finish;
    Trie() : go{}, cnt(0), finish(0) {}
};
Trie* root;

int trie_insert(const string key){
    int ret = 0;
    Trie* now = root;

    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'a';
        for(int j=nxt+1; j<26; j++){
            if(now->go[j] != NULL)
                ret += now->go[j]->cnt;
        }

        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
        now->cnt++;
    }
    now->finish++;
    for(int i=0; i<26; i++){
        if(now->go[i] != NULL)
            ret += now->go[i]->cnt;
    }
    return ret;
}

char tmp[50];
vector<string> strs;

int main()
{
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%s", tmp);
        strs.push_back(tmp);
    }
    sort(strs.begin(), strs.end());


    root = new Trie();
    ll ans = 0;
    for(int i=0; i<strs.size(); i++){
        reverse(strs[i].begin(), strs[i].end());
        ans += trie_insert(strs[i]);
    }
    printf("%lld\n", ans);
	return 0;
}
