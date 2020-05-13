#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;
const int MX = 2005;

struct Hash{
    ll power;
    ll powv[MX];
    Hash(int p){
        power = p;
        powv[0] = 1;
        for(int i=1; i<MX; i++)
            powv[i] = (powv[i-1] * power) % MOD;
    }
    ll compute(vector<ll>& arr){
        ll ret = 0;
        for(int i=0; i<arr.size(); i++){
            ret = (ret * power) % MOD;
            ret = (ret + arr[i]) % MOD;
        }
        return ret;
    }
    ll next(int siz, ll phash, ll delv, ll newv){
        ll ret = phash;
        ret = ((ret - delv * powv[siz-1] % MOD) + MOD) % MOD;
        ret = (ret * power) % MOD;
        ret = (ret + newv) % MOD;
        return ret;
    }
};
Hash hsh1(3), hsh2(7);
int h1, w1, h2, w2;
char small[2005][2005];
char big[2005][2005];

ll shash;
ll bhash1[2005][2005];
ll bhash2[2005][2005];

void compute_shash(){
    vector<ll> v1, v2;
    for(int i=0; i<h1; i++){
        v1.clear();
        for(int j=0; j<w1; j++)
            v1.push_back(small[i][j]);
        v2.push_back(hsh1.compute(v1));
    }
    shash = hsh2.compute(v2);
}
void compute_bhash(){
    vector<ll> v1;
    for(int i=0; i<h2; i++){
        v1.clear();
        for(int j=0; j<w1; j++)
            v1.push_back(big[i][j]);
        bhash1[i][w1-1] = hsh1.compute(v1);

        for(int j=w1; j<w2; j++)
            bhash1[i][j] = hsh1.next(w1, bhash1[i][j-1], big[i][j-w1], big[i][j]);
    }
    for(int j=w1-1; j<w2; j++){
        v1.clear();
        for(int i=0; i<h1; i++)
            v1.push_back(bhash1[i][j]);
        bhash2[h1-1][j] = hsh2.compute(v1);

        for(int i=h1; i<h2; i++)
            bhash2[i][j] = hsh2.next(h1, bhash2[i-1][j], bhash1[i-h1][j], bhash1[i][j]);
    }
}
int compute_ans(){
    int ans = 0;
    for(int i=h1-1; i<h2; i++){
        for(int j=w1-1; j<w2; j++){
            if(shash == bhash2[i][j])
                ans++;
        }
    }
    return ans;
}

int main()
{
    scanf("%d %d %d %d", &h1, &w1, &h2, &w2);
    for(int i=0; i<h1; i++)
        scanf(" %s", small[i]);
    for(int i=0; i<h2; i++)
        scanf(" %s", big[i]);

    compute_shash();
    compute_bhash();
    printf("%d\n", compute_ans());
    return 0;
}
