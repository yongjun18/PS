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

char arr1[2020][2020];
char arr2[2020][2020];
int code1[2020];
int cfail[2020];
int code2[2020][2020];
vector<string> str1;

void get_cfail(int n1){
    int match = 0;
    for(int last=1; last<n1; last++){
        while(match > 0 && code1[last] != code1[match])
            match = cfail[match-1];
        if(code1[last] == code1[match]) match++;
        cfail[last] = match;
    }
}


int main()
{
    int n1, m1, n2, m2;
    scanf("%d %d %d %d", &n1, &m1, &n2, &m2);
    for(int i=0; i<n1; i++)
        scanf("%s", arr1[i]);
    for(int i=0; i<n2; i++)
        scanf("%s", arr2[i]);

    for(int i=0; i<n1; i++)
        str1.push_back(arr1[i]);
    sort(str1.begin(), str1.end());
    str1.erase(unique(str1.begin(), str1.end()), str1.end());

    root = new Trie();
    for(int i=0; i<str1.size(); i++)
        trie_insert(str1[i], i);
    build_fail();

    for(int i=0; i<n1; i++){
        Trie* now = root;
        for(int j=0; j<m1; j++){
            int c = arr1[i][j] - 'a';
            while(now != root && now->go[c] == NULL)
                now = now->fail;
            if(now->go[c])
                now = now->go[c];
        }
        code1[i] = now->finish;
    }
    for(int i=0; i<n2; i++){
        Trie* now = root;
        for(int j=0; j<m2; j++){
            int c = arr2[i][j] - 'a';
            while(now != root && now->go[c] == NULL)
                now = now->fail;
            if(now->go[c])
                now = now->go[c];
            code2[i][j] = now->finish;
        }
    }
    get_cfail(n1);
    int ans = 0;
    for(int j=0; j<m2; j++){
        int match = 0;
        for(int last=0; last<n2; last++){
            while(match > 0 && code2[last][j] != code1[match])
                match = cfail[match-1];
            if(code2[last][j] == code1[match]) match++;
            if(match == n1){
                ans++;
                match = cfail[match-1];
            }
        }
    }
    printf("%d\n", ans);
	return 0;
}
