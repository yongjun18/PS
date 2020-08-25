#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Hash{
    static const int MX = 2005;
    ll power, powv[MX];
    int len;
    vector<ll> st, val;

    void init(ll power, int len){
        this->power = power;
        this->len = len;
        powv[0] = 1;
        for(int i=1; i<MX; i++)
            powv[i] = (powv[i-1] * power) % MOD;
    }

    ll get_val(){
        if(st.size() >= len)
            return val.back();
        else return -1;
    }

    void insert(ll x){
        ll nxt;
        if(st.size() == 0) nxt = 0;
        else nxt = val.back();

        if(st.size() >= len){
            ll del = st[st.size()-len];
            nxt = ((nxt - del * powv[len-1] % MOD) + MOD) % MOD;
        }
        nxt = (nxt * power) % MOD;
        nxt = (nxt + x) % MOD;
        st.push_back(x);
        val.push_back(nxt);
    }

    void pop(){
        st.pop_back();
        val.pop_back();
    }

    void clear(){
        st.clear();
        val.clear();
    }
};
Hash hs1, hs2;

char p1[2010][2010];
char p2[2010][2010];
ll hashv1;
ll hashv2[2010][2010];

int main()
{
    int h1, w1, h2, w2;
    int ans;
    scanf("%d %d %d %d", &h1, &w1, &h2, &w2);

    for(int i=0; i<h1; i++)
        scanf("%s", p1[i]);
    for(int i=0; i<h2; i++)
        scanf("%s", p2[i]);

    hs1.init(13, w1);
    hs2.init(17, h1);

    for(int i=0; i<h1; i++){
        hs1.clear();
        for(int j=0; j<w1; j++)
            hs1.insert(p1[i][j]);
        hs2.insert(hs1.get_val());
    }
    hashv1 = hs2.get_val();

    for(int i=0; i<h2; i++){
        hs1.clear();
        for(int j=0; j<w2; j++){
            hs1.insert(p2[i][j]);
            hashv2[i][j] = hs1.get_val();
        }
    }
    for(int j=0; j<w2; j++){
        hs2.clear();
        for(int i=0; i<h2; i++){
            hs2.insert(hashv2[i][j]);
            hashv2[i][j] = hs2.get_val();
        }
    }

    ans = 0;
    for(int i=0; i<h2; i++){
        for(int j=0; j<w2; j++){
            if(hashv1 == hashv2[i][j])
                ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
