#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e7;
const int MOD = 1e9+7;

int n;
int aa[201010];
int ka[201010];
int bb[201010];
int kb[201010];

int matchA[201010], matchB[401010];
int level[201010];
vector<int> adj[201010];

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
            if (matchA[i] == -1 && dfs(i))
                flow++;
        }
        if (flow == 0) break;
        match += flow;
    }
    return match;
}

int solve(ll x){
    for(int i=0; i<n; i++){
        adj[i].clear();
        if(ka[i] <= x)  adj[i].push_back(aa[i]);
        if(kb[i] <= x)  adj[i].push_back(bb[i]);
    }
    return Hopcroft_Karp(n, 2*n) == n;
}
ll binary_search(ll x, ll y) {
    ll lo = x - 1;
    ll hi = y + 1;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (solve(mid)) hi = mid;
        else lo = mid;
    }
    return hi;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d %d", &aa[i], &ka[i], &bb[i], &kb[i]);
        aa[i]--;
        bb[i]--;
    }

    ll ans = binary_search(0, INF);
    if(ans > INF) printf("-1\n");
    else printf("%lld\n", ans);
    return 0;
}
