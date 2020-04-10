#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
int arr[100][100];
int vnum[100][100];
int hnum[100][100];

vector<int> matchA, matchB;
vector< vector<int> > adj;
vector<int> visit;

int dfs(int a) {
	visit[a] = 1;
	for (int b : adj[a]) {
		if (matchB[b] == -1 || (!visit[matchB[b]] && dfs(matchB[b]))) {
			matchA[a] = b;
			matchB[b] = a;
			return 1;
		}
	}
	return 0;
}
int bipartite_matching(int hcnt, int vcnt) {
	int match = 0;
	matchA.resize(hcnt, -1);
	matchB.resize(vcnt, -1);
	adj.resize(hcnt, vector<int>());

	for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == 0){
                adj[hnum[i][j]].push_back(vnum[i][j]);
            }
        }
	}
	for (int i=0; i<hcnt; i++) {
	    if (matchA[i] == -1) {
            visit.clear();
	        visit.resize(hcnt, 0);
	        if (dfs(i)) match++;
	    }
	}
	return match;
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            scanf("%d", &arr[i][j]);
    }

    int hcnt = 0;
    int vcnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == 2) continue;
            if(j > 0 && arr[i][j-1] != 2) hnum[i][j] = hnum[i][j-1];
            else hnum[i][j] = hcnt++;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(arr[i][j] == 2) continue;
            if(i > 0 && arr[i-1][j] != 2) vnum[i][j] = vnum[i-1][j];
            else vnum[i][j] = vcnt++;
        }
    }
    printf("%d\n", bipartite_matching(hcnt, vcnt));
    return 0;
}
