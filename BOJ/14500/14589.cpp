#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Line{
    int x, y, num;
    bool operator <(const Line& rhs) const{
        if(y != rhs.y) return y < rhs.y;
        return x < rhs.x;
    }
};
vector<Line> lines;
vector<Line> input;
int ri[150100][19];

void build(int n){
    sort(lines.begin(), lines.end());
    int now = n-1;
    for(int i=n-1; i>=0; i--){
        while(lines[i].y < lines[now].x) now--;
        ri[lines[i].num][0] = lines[now].num;
    }
    for(int j=1; j<19; j++){
        for(int i=0; i<n; i++)
            ri[i][j] = ri[ri[i][j-1]][j-1];
    }
}
int query(int a, int b){
    if(input[a].x > input[b].x)
        swap(a, b);

    int ans = 0;
    int now = a;
    for(int i=18; i>=0; i--){
        int nxt = ri[now][i];
        if(input[nxt].y < input[b].x){
            now = nxt;
            ans += (1<<i);
        }
    }
    if(input[b].x <= input[now].y) ans += 1;
    else ans += 2;

    if(ans > 150100) return -1;
    else return ans;
}

int main()
{
    int n, q;
    scanf("%d", &n);
    input.resize(n);
    for(int i=0; i<n; i++){
        scanf("%d %d", &input[i].x, &input[i].y);
        input[i].num = i;
    }
    lines = input;
    build(n);

    scanf("%d", &q);
    while(q--){
        int a, b;
        scanf("%d %d", &a, &b); a--; b--;
        printf("%d\n", query(a, b));
    }
    return 0;
}
