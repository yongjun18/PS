#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int visit[1010][1010];
vector<int> adj[1010][21];

int ctrl[1010];
int milb[1010];

void dfs(int x, int y, int c){
	for (int i = 1; i <= c; i++){
		for (int nx : adj[x][i]){
			for (int ny : adj[y][i]){
				if (visit[nx][ny] == 1) continue;

				visit[nx][ny] = 1;
				dfs(nx, ny, c);
			}
		}
	}
}

int main()
{
	int n, w, c, h, m;
	int ok;

	scanf("%d %d %d %d %d", &n, &w, &c, &h, &m);

	for (int i = 0; i < h; i++){
		int x;
		scanf("%d", &x);
		ctrl[x] = 1;
	}
	for (int i = 0; i < m; i++){
		int x;
		scanf("%d", &x);
		milb[x] = 1;
	}

	for (int i = 0; i < w; i++){
		int s, c, t;
		scanf("%d %d %d", &s, &c, &t);
		adj[s][c].push_back(t);
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (ctrl[i] == 1 && ctrl[j] == 0 && visit[i][j] == 0){
				visit[i][j] = 1;
				dfs(i, j, c);
			}
		}
	}

	ok = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (milb[i] == 1 && milb[j] == 1 && visit[i][j] == 1){
				ok = 1;
			}
		}
	}
	printf("%s\n", ok ? "YES" : "NO");
	return 0;
}
