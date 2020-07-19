#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Node{ int s, t, a, b; };
int dp[4][4][210][210];
Node pv[4][4][210][210];

void update(Node now, Node nxt){
    if(nxt.a > 200 || nxt.b > 200) return;
    dp[nxt.s][nxt.t][nxt.a][nxt.b] = 1;
    pv[nxt.s][nxt.t][nxt.a][nxt.b] = now;
}
void build_dp(){
    dp[0][0][0][0] = 1;
    for(int s=0; s<=2; s++){
        for(int t=0; t<=2; t++){
            for(int a=0; a<=200; a++){
                for(int b=0; b<=200; b++){
                    if(dp[s][t][a][b] == 0) continue;

                    Node now = { s, t, a, b };
                    int winp = 25;
                    if(s+t == 4) winp = 15;

                    for(int i=0; i<=winp-2; i++){
                        update(now, {s+1, t, a+winp, b+i});
                        update(now, {s, t+1, a+i, b+winp});
                    }
                    for(int i=1; i<=200; i++){
                        update(now, {s+1, t, a+winp+i, b+winp-2+i});
                        update(now, {s, t+1, a+winp-2+i, b+winp+i});
                    }
                }
            }
        }
    }
}
void print_ans(Node now){
    vector< pair<int,int> > ans;
    printf("%d:%d\n", now.s, now.t);

    while(1){
        if(now.s == 0 && now.t == 0) break;
        Node p = pv[now.s][now.t][now.a][now.b];
        ans.push_back({now.a-p.a, now.b-p.b});
        now = p;
    }
    reverse(ans.begin(), ans.end());
    for(auto it : ans)
        printf("%d:%d ", it.first, it.second);
    printf("\n");
}
int main()
{
    int t;
    scanf("%d", &t);
    build_dp();
    while(t--){
        int a, b;
        scanf("%d %d", &a, &b);

        if(dp[3][0][a][b] == 1) print_ans({3, 0, a, b});
        else if(dp[3][1][a][b] == 1) print_ans({3, 1, a, b});
        else if(dp[3][2][a][b] == 1) print_ans({3, 2, a, b});
        else if(dp[2][3][a][b] == 1) print_ans({2, 3, a, b});
        else if(dp[1][3][a][b] == 1) print_ans({1, 3, a, b});
        else if(dp[0][3][a][b] == 1) print_ans({0, 3, a, b});
        else printf("Impossible\n");
    }
    return 0;
}
