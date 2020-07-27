#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[20];
vector< vector<int> > SCC;

stack<int> st;
int dfsn[20];
int visit[20];
int finish[20];
int cnt = 0;
int snum[20];
int scnt = 0;

int dfs(int x) {
    visit[x] = 1;
    dfsn[x] = cnt++;
    st.push(x);

    int minv = dfsn[x];
    for (int next : adj[x]) {
        if (!visit[next]) minv = min(minv, dfs(next));
        else if (!finish[next]) minv = min(minv, dfsn[next]);
    }
    if (minv == dfsn[x]) {
        vector<int> now_scc;
        while (1) {
            int top = st.top(); st.pop();
            snum[top] = scnt;

            now_scc.push_back(top);
            finish[top] = 1;
            if (top == x) break;
        }
        SCC.push_back(now_scc);
        scnt++;
    }
    return minv;
}
int get_SCC(int n) {
    for (int i = 1; i <= n; i++) {
        if (!visit[i]) dfs(i);
    }
    return SCC.size();
}

char ans[20][3][200];

void init(){
    for(int i=0; i<20; i++){
        for(int j=0; j<3; j++){
            for(int k=0; k<200; k++){
                if(i%2 == 0) ans[i][j][k] = '.';
                else{
                    if(j==2 || k<9) ans[i][j][k] = '#';
                    else ans[i][j][k] = '.';
                }
            }
        }
    }
    for(int i=0; i<20; i++){
        for(int k=10; k<200; k+=2)
            ans[i][1][k] = '#';
    }
}
void add_edge(int ecnt, int l1, int l2){
    ans[l1][1][10+ecnt*2] = '.';
    ans[l2][1][10+ecnt*2] = '.';

    ans[l2+1][0][10+ecnt*2] = '#';
}

int main()
{
    int n, ecnt;

    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            int x;
            scanf("%d", &x);
            if(x == 1) adj[i].push_back(j);
        }
    }
    init();
    get_SCC(n);

    for(int i=scnt-1; i>=0; i--){
        for(int now :SCC[i])
            ans[(scnt-1-i)*2][0][now-1] = '0'+now;
    }
    ecnt = 0;
    for(int i=1; i<=n; i++){
        for(int nxt :adj[i]){
            if(snum[i] != snum[nxt]){
                int from = (scnt-1-snum[i])*2;
                int to = (scnt-1-snum[nxt])*2;
                if(from > to) swap(from, to);

                add_edge(ecnt, from, to);
                ecnt++;
            }
        }
    }
    printf("200 3 20\n");
    for(int i=0; i<20; i++){
        for(int j=0; j<3; j++){
            for(int k=0; k<200; k++)
                printf("%c", ans[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
