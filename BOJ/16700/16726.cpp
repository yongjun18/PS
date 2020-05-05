#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int matchA[2701], matchB[2701];
int level[2701];
vector<int> adj[2701];
void bfs(int n) {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (matchA[i] == -1) {
            level[i] = 0;
            q.push(i);
        }
        else level[i] = INF;
    }
    while (!q.empty()) {
        int a = q.front(); q.pop();
        for (int b : adj[a]) {
            if (matchB[b] != -1 && level[matchB[b]] == INF) {
                level[matchB[b]] = level[a] + 1;
                q.push(matchB[b]);
            }
        }
    }
}
int dfs(int a) {
    for (int b : adj[a]) {
        if (matchB[b] == -1 || (level[matchB[b]] == level[a] + 1 && dfs(matchB[b]))) {
            matchA[a] = b;
            matchB[b] = a;
            return 1;
        }
    }
    return 0;
}
int Hopcroft_Karp(int n, int m) {
    int match = 0;
    memset(matchA, -1, sizeof(matchA));
    memset(matchB, -1, sizeof(matchB));
    while (1) {
        bfs(n);
        int flow = 0;
        for (int i = 0; i < n; i++) {
            if (matchA[i] == -1 && dfs(i)) flow++;
        }
        if (flow == 0) break;
        match += flow;
    }
    return match;
}

int n, m;
char arr[51][51];
int num[51][51];

int valid(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}
void connect(){
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if((i+j)%2 == 0) continue;
            if(arr[i][j] == 'X') continue;

            for(int d=0; d<4; d++){
                int nx = i+dx[d];
                int ny = j+dy[d];
                if(valid(nx,ny) && arr[nx][ny] == '.')
                    adj[num[i][j]].push_back(num[nx][ny]);
            }
        }
    }
}
int main()
{
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++)
        scanf("%s", arr[i]);

    int number = 0;
    int floor = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == '.') floor++;
            num[i][j] = number++;
        }
    }
    connect();

    int flow = Hopcroft_Karp(n*m, n*m);
    printf("%d\n", floor-flow);
    return 0;
}
