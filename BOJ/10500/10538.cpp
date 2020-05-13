#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    Trie* fail;
    int finish;
    Trie() : go{}, fail(0), finish(-1) {}
};
Trie* root;
void trie_insert(const string key, int num){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'a';
        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
    }
    now->finish = num;
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

char small[2005][2005];
char big[2005][2005];
vector<string> smlstr;

int bignum[2005][2005];
int smlnum[2005];
int sfail[2005];

void build_smlstr(int h1){
    for(int i=0; i<h1; i++)
        smlstr.push_back(string(small[i]));
    sort(smlstr.begin(), smlstr.end());
    smlstr.erase(unique(smlstr.begin(), smlstr.end()), smlstr.end());

    root = new Trie();
    for(int i=0; i<smlstr.size(); i++)
        trie_insert(smlstr[i], i);
    build_fail();
}
void build_bignum(int h2, int w2){
    for(int i=0; i<h2; i++){
        Trie* now = root;
        for(int j=0; j<w2; j++){
            int nxt = big[i][j] - 'a';
            while(now != root && now->go[nxt] == NULL)
                now = now->fail;
            if(now->go[nxt])
                now = now->go[nxt];

            bignum[i][j] = now->finish;
        }
    }
}
void build_smlnum(int h1, int w1){
    for(int i=0; i<h1; i++){
        Trie* now = root;
        for(int j=0; j<w1; j++){
            int nxt = small[i][j] - 'a';
            while(now != root && now->go[nxt] == NULL)
                now = now->fail;
            if(now->go[nxt])
                now = now->go[nxt];
        }
        smlnum[i] = now->finish;
    }
}
void build_sfail(int h1){
    int match = 0;
    for(int last=1; last<h1; last++){
        while(match > 0 && smlnum[last] != smlnum[match])
            match = sfail[match-1];
        if(smlnum[last] == smlnum[match]) match++;
        sfail[last] = match;
    }
}
int get_ans(int h1, int w1, int h2, int w2){
    int ans = 0;
    for(int j=0; j<w2; j++){
        int match = 0;
        for(int i=0; i<h2; i++){
            while(match > 0 && bignum[i][j] != smlnum[match])
                match = sfail[match-1];
            if(bignum[i][j] == smlnum[match]) match++;
            if(match == h1){
                ans++;
                match = sfail[match-1];
            }
        }
    }
    return ans;
}
int main()
{
    int h1, w1, h2, w2;
    scanf("%d %d %d %d", &h1, &w1, &h2, &w2);
    for(int i=0; i<h1; i++)
        scanf("%s", small[i]);
    for(int i=0; i<h2; i++)
        scanf("%s", big[i]);

    build_smlstr(h1);
    build_bignum(h2, w2);
    build_smlnum(h1, w1);
    build_sfail(h1);
    printf("%d\n", get_ans(h1, w1, h2, w2));
    return 0;
}
