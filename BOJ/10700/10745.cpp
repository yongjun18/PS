#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    Trie* fail;
    int finish;
    Trie() : go{}, fail(0), finish(0) {}
};
Trie* root;
void trie_insert(const string key){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'a';
        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
    }
    now->finish = key.size();
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
//                if(nxt->fail->finish)
//                    nxt->finish = nxt->fail->finish;
                q.push(nxt);
            }
        }
    }
}
Trie* step(Trie* now, char ch){
    Trie* pv = now;
    int nxt = ch -'a';
    while(now != root && now->go[nxt] == NULL)
        now = now->fail;
    if(now->go[nxt])
        now = now->go[nxt];
    pv->go[nxt] = now;
    return now;
}

char str[101010];
char tmp[101010];
vector< pair<char,Trie*> > ans;

int main()
{
    int n;
    scanf("%s", str);
    scanf("%d", &n);
    root = new Trie();
    for(int i=0; i<n; i++){
        scanf("%s", tmp);
        trie_insert(tmp);
    }
    build_fail();

    ans.push_back({0, root});
    for(int i=0; str[i]; i++){
        Trie* now = step(ans.back().second, str[i]);

        ans.push_back({str[i], now});
        if(now->finish)
            ans.resize(ans.size() - now->finish);
    }
    for(int i=1; i<ans.size(); i++)
        printf("%c", ans[i].first);
    printf("\n");
	return 0;
}
