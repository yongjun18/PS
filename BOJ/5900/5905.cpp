#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[3];
    Trie* fail;
    int finish;
    Trie() : go{}, fail(0), finish(0) {}
};
Trie* root;

void trie_insert(const string key){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'A';
        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
    }
    now->finish++;
}
void build_fail(){
    root->fail = root;
    queue<Trie*> q;

    for(int i=0; i<3; i++){
        Trie* nxt = root->go[i];
        if(nxt != NULL){
            nxt->fail = root;
            q.push(nxt);
        }
    }
    while(q.size()){
        Trie* now = q.front(); q.pop();

        for(int i=0; i<3; i++){
            Trie* nxt = now->go[i];
            if(nxt != NULL){
                Trie* dest = now->fail;
                while(dest != root && dest->go[i] == NULL)
                    dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                nxt->fail = dest;

                if(nxt->fail->finish)
                    nxt->finish += nxt->fail->finish;
                q.push(nxt);
            }
        }
    }
}
char tmp[30];
int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    root = new Trie();
    for(int i=0; i<n; i++){
        scanf("%s", tmp);
        trie_insert(tmp);
    }
    build_fail();


    map<Trie*, int> dp, ndp;
    dp[root] = 0;

    for(int i=0; i<k; i++){
        for(auto it : dp){
            Trie* nd = it.first;
            int val = it.second;

            for(int j=0; j<3; j++){
                Trie* nxt = nd;
                while(nxt != root && nxt->go[j] == NULL) nxt = nxt->fail;
                if(nxt->go[j]) nxt = nxt->go[j];
                ndp[nxt] = max(ndp[nxt], val + nxt->finish);
            }
        }
        swap(dp, ndp);
        ndp.clear();
    }

    int ans = 0;
    for(auto it : dp)
        ans = max(ans, it.second);
    printf("%d\n", ans);
	return 0;
}
