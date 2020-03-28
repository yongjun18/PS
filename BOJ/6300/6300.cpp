#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Trie{
    Trie* go[26];
    Trie* fail;
    vector<int> finish;
    Trie() : go{}, fail(0), finish(0) {}
};
Trie* root;
void trie_insert(const string& key, int num){
    Trie* now = root;
    for(int i=0; i<key.size(); i++){
        int nxt = key[i] - 'A';
        if(now->go[nxt] == NULL)
            now->go[nxt] = new Trie();
        now = now->go[nxt];
    }
    now->finish.push_back(num);
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

                for(auto it : nxt->fail->finish)
                    nxt->finish.push_back(it);
                q.push(nxt);
            }
        }
    }
}
int n, m, w;
char arr[1010][1010];
string strs[1010];
char tmp[1010];
pair< pair<int,int>, char > ans[1010];

void check(int x, int y, int dx, int dy, char dir){
    Trie* now = root;

    while(0 <= x && x < n && 0 <= y && y < m){
        int c = arr[x][y]-'A';
        while(now != root && now->go[c] == NULL)
            now = now->fail;
        if(now->go[c]) now = now->go[c];

        for(auto it : now->finish){
            int px = x - dx*(strs[it].size() - 1);
            int py = y - dy*(strs[it].size() - 1);
            ans[it] = min(ans[it], {{px, py}, dir});
        }
        x += dx;
        y += dy;
    }
}

int main()
{
    scanf("%d %d %d", &n, &m, &w);
    for(int i=0; i<n; i++)
        scanf("%s", arr[i]);

    root = new Trie();
    for(int i=0; i<w; i++){
        scanf("%s", tmp);
        strs[i] = tmp;
        trie_insert(strs[i], i);
        ans[i] = {{1010, 1010}, 'I'};
    }
    build_fail();

    int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int dy[] = { 0, 1, 1, 1, 0, -1 ,-1, -1 };
    for(int i=0; i<8; i++){
        for(int j=0; j<n; j++){
            check(j, 0, dx[i], dy[i], "ABCDEFGH"[i]);
            check(j, m-1, dx[i], dy[i], "ABCDEFGH"[i]);
        }
        for(int j=0; j<m; j++){
            check(0, j, dx[i], dy[i], "ABCDEFGH"[i]);
            check(n-1, j, dx[i], dy[i], "ABCDEFGH"[i]);
        }
    }
    for(int i=0; i<w; i++){
        int x = ans[i].first.first;
        int y = ans[i].first.second;
        char c = ans[i].second;
        printf("%d %d %c\n", x, y, c);
    }
	return 0;
}
