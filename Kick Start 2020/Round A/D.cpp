#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    int cnt, finish, match, len;
    Trie() : go{}, cnt(0), finish(0), match(0), len(0) {}
};
Trie* root;
vector<Trie*> nodes;

void trie_insert(const string key){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'A';
        if(now->go[nxt] == NULL){
            now->go[nxt] = new Trie();
            now->go[nxt]->len = now->len+1;
            nodes.push_back(now->go[nxt]);
        }
        now = now->go[nxt];
        now->cnt++;
    }
    now->finish++;
}
int cmp(Trie* t1, Trie* t2){
    return t1->len < t2->len;
}

char str[2010101];

int main()
{
    int t;
    scanf("%d", &t);

    for(int test=1; test<=t; test++){
        root = new Trie();
        nodes.clear();

        int n, k;
        scanf("%d %d", &n, &k);
        for(int i=0; i<n; i++){
            scanf("%s", str);
            trie_insert(str);
        }
        sort(nodes.begin(), nodes.end(), cmp);

        int ans = 0;
        for(int i=(int)nodes.size()-1; i>=0; i--){
            for(int nxt=0; nxt<26; nxt++){
                if(nodes[i]->go[nxt] != NULL)
                    nodes[i]->match += nodes[i]->go[nxt]->match;
            }
            int left = nodes[i]->cnt - nodes[i]->match;
            int q = left/k;
            ans += q * nodes[i]->len;
            nodes[i]->match += q*k;
        }
        printf("Case #%d: ", test);
        printf("%d\n", ans);
    }
	return 0;
}
