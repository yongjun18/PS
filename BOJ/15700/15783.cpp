#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[100100];
vector< vector<int> > SCC;

stack<int> st;
int dfsn[100100];
int visit[100100];
int finish[100100];
int cnt = 0;
int snum[100100];
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
    for (int i = 0; i < n; i++) {
        if (!visit[i]) dfs(i);
    }
    return SCC.size();
}

int indegree[100100];

int main()
{
    int n, m, ans;
    scanf("%d %d", &n, &m);
    while(m--){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
    }
    get_SCC(n);
    for(int i=0; i<SCC.size(); i++){
        for(int now : SCC[i]){
            for(int nxt : adj[now]){
                if(snum[now] != snum[nxt])
                    indegree[ snum[nxt] ]++;
            }
        }
    }
    ans = 0;
    for(int i=0; i<scnt; i++){
        if(indegree[i] == 0)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
