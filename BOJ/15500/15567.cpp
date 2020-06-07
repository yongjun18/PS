#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[500];
vector< vector<int> > SCC;
stack<int> st;

int dfsn[500];
int visit[500];
int finish[500];
int cnt = 0;
int snum[500];
int scnt = 0;
int result[500];

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
    for (int i = 0; i < n; i++) {
        if (!visit[i]) dfs(i);
    }
    return SCC.size();
}
void closure(int x, int xbool, int y, int ybool) {
    adj[x * 2 + !xbool].push_back(y * 2 + ybool);
    adj[y * 2 + !ybool].push_back(x * 2 + xbool);
}
int can_true(int n) {
    for (int i = 0; i < n; i++) {
        if (snum[2*i] == snum[2*i + 1])
            return 0;
    }
    memset(result, -1, sizeof(result));
    for (int i = scnt - 1; i >= 0; i--) {
        for (int now : SCC[i]) {
            if (result[now] != -1) continue;
            result[now] = 0;
            result[now ^ 1] = 1;
        }
    }
    return 1;
}

int arr[100][4];
int ncnt = 0;
int num[100][100];
vector<int> lotus[100];

int ans[100];

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        for(int j=0; j<4; j++)
            scanf("%d", &arr[i][j]);
    }
    memset(num, -1, sizeof(num));
    for(int i=0; i<n; i++){
        int a, b;
        scanf("%d %d", &a, &b); a--; b--;
        if(a != b){
            num[i][a] = ncnt++;
            num[i][b] = ncnt++;
            closure(num[i][a], 1, num[i][b], 1);
            closure(num[i][a], 0, num[i][b], 0);
            lotus[a].push_back(i);
            lotus[b].push_back(i);
        }
        else{
            num[i][a] = ncnt++;
            closure(num[i][a], 1, num[i][a], 1);
            lotus[a].push_back(i);
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<lotus[i].size(); j++){
            for(int k=j+1; k<lotus[i].size(); k++){
                int a = lotus[i][j];
                int b = lotus[i][k];
                closure(num[a][i], 0, num[b][i], 0);
            }
        }
    }
    while(m--){
        int l1, l2, t;
        scanf("%d %d %d", &l1, &l2, &t); l1--; l2--; t--;
        for(int a : lotus[l1]){
            for(int b : lotus[l2]){
                if(arr[a][t] != arr[b][t]){
                    closure(num[a][l1], 0, num[b][l2], 0);
                }
            }
        }
    }
    get_SCC(2*ncnt);
    if(can_true(ncnt)){
        printf("YES\n");
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(num[i][j] != -1 && result[2*num[i][j]+1] == 1)
                    ans[j] = i;
            }
        }
        for(int i=0; i<n; i++)
            printf("%d ", ans[i]+1);
    }
    else printf("NO\n");
    return 0;
}
