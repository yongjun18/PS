#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[100];
    int no, del;
    Trie() : go{}, no(0), del(0) {}
};
Trie* root;
vector<Trie*> used;
void trie_insert(const string key, int no, int del){
    Trie* now = root;
    root->no += no;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i]-' ';
        if(now->go[nxt] == NULL)
            used.push_back(now->go[nxt] = new Trie());
        now = now->go[nxt];
        now->no += no;
    }
    now->del += del;
}
int dfs(Trie* now){
    if(now->no == 0) return 1;

    int ret = 0;
    if(now->del > 0) ret++;

    for(int i=0; i<100; i++){
        if(now->go[i] != NULL)
            ret += dfs(now->go[i]);
    }
    return ret;
}

char tmp[30];
int main()
{
    int t;
    scanf("%d", &t);

    while(t--){
        root = new Trie();
        int n, m;

        scanf("%d", &n);
        while(n--){
            scanf("%s", tmp);
            trie_insert(tmp, 0, 1);
        }

        scanf("%d", &m);
        while(m--){
            scanf("%s", tmp);
            trie_insert(tmp, 1, 0);
        }
        printf("%d\n", dfs(root));

        delete(root);
        for(auto it : used) delete(it);
        used.clear();
    }
	return 0;
}
