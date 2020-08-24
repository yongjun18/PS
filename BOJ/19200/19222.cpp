#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
int vote[105][105];
vector<int> ans;

struct Node{
    int xvote, ovote, num;
    bool operator < (const Node& rhs) const{
        return ovote - xvote < rhs.ovote - rhs.xvote;
    }
};
void king_make(int x){
    vector<Node> vec;
    int xsum = 0;
    int osum = 0;
    int last = -1;

    for(int i=0; i<m; i++)
        vec.push_back({vote[i][x], vote[i][n-1], i});
    sort(vec.begin(), vec.end());

    for(int i=0; i<vec.size(); i++){
        if(xsum + vec[i].xvote < osum + vec[i].ovote)
            break;
        last = i;
        xsum += vec[i].xvote;
        osum += vec[i].ovote;
    }
    if(m-1-last < ans.size()){
        ans.clear();
        for(int i=last+1; i<vec.size(); i++)
            ans.push_back(vec[i].num);
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            scanf("%d", &vote[i][j]);
    }
    ans.resize(101);
    for(int i=0; i<n-1; i++)
        king_make(i);

    printf("%d\n", ans.size());
    for(int it : ans)
        printf("%d ", it+1);
    printf("\n");
    return 0;
}
