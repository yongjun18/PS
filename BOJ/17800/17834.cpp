#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector<int> adj[50010];
int odd[50010];

int ocnt = 0;
int bfs(int start){
    memset(odd, -1, sizeof(odd));
    queue<int> que;
    que.push(start);
    odd[start] = 0;

    while(que.size()){
        int now = que.front(); que.pop();
        for(int nxt : adj[now]){
            if(odd[nxt] == -1){
                que.push(nxt);
                odd[nxt] = !odd[now];
                if(odd[nxt]) ocnt++;
            }
            else if(odd[nxt] == odd[now])
                return 0;
        }
    }
    return 1;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    while(m--){
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    if(bfs(1) == 1) printf("%lld\n", (ll)ocnt * (n-ocnt) * 2);
    else printf("0\n");
    return 0;
}
