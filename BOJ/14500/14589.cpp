#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector< pair<int,int> > line;
int unum;
int le[300100][20];
int ri[300100][20];

void compress(){
    vector<int> used;
    for(auto it : line){
        used.push_back(it.first);
        used.push_back(it.second);
    }
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());
    unum = used.size();

    for(auto &it : line){
        it.first = lower_bound(used.begin(), used.end(), it.first)-used.begin();
        it.second = lower_bound(used.begin(), used.end(), it.second)-used.begin();
    }
}
int cmp(pair<int,int> a, pair<int,int> b){
    swap(a.first, a.second);
    swap(b.first, b.second);
    return a < b;
}
void build(int n){
    memset(le, -1, sizeof(le));
    memset(ri, -1, sizeof(ri));
    vector< pair<int,int> > tmp = line;
    sort(tmp.begin(), tmp.end());
    int from = 0;
    for(int i=0; i<n; i++){
        while(tmp[from].second < tmp[i].first)
            from++;
        le[tmp[i].first][0] = tmp[from].first;
    }
    sort(tmp.begin(), tmp.end(), cmp);
    from = n-1;
    for(int i=n-1; i>=0; i--){
        while(tmp[i].second < tmp[from].first)
            from--;
        ri[tmp[i].second][0] = tmp[from].second;
    }
    for(int j=1; j<20; j++){
        for(int i=0; i<unum; i++){
            if(le[i][0] != -1)
                le[i][j] = le[le[i][j-1]][j-1];
            if(ri[i][0] != -1)
                ri[i][j] = ri[ri[i][j-1]][j-1];
        }
    }
}
int query(int a, int b){
    int ans = 0;
    int l = line[a].first;
    int r = line[a].second;

    for(int i=19; i>=0; i--){
        int tmpl = le[l][i];
        int tmpr = ri[r][i];
        if(tmpr < line[b].first || line[b].second < tmpl){
            ans += (1<<i);
            l = tmpl;
            r = tmpr;
        }
    }
    if(line[a].second < line[b].first || line[b].second < line[a].first)
        ans++;
    ans++;
    if(ans > 150100) return -1;
    else return ans;
}

int main()
{
    int n, q;
    scanf("%d", &n);
    line.resize(n);
    for(int i=0; i<n; i++)
        scanf("%d %d", &line[i].first, &line[i].second);
    compress();
    build(n);

    scanf("%d", &q);
    while(q--){
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        printf("%d\n", query(a, b));
    }
    return 0;
}
