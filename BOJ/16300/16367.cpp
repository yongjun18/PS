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

vector<int> adj[20000];
vector< vector<int> > SCC;

int dfsn[20000];
int visit[20000];
int finish[20000];
int cnt = 0;
stack<int> st;

int snum[20000];
int scnt = 0;

int result[20000];

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

int get_result(int n) {
	for (int i = 0; i < n; i++) {
		if (snum[2 * i] == snum[2 * i + 1])
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

int main()
{
	int n, m;
	int ok;

	scanf("%d %d", &n, &m);

	while (m--){
		int x1, x2, x3;
		char c1, c2, c3;
		scanf("%d %c %d %c %d %c", &x1, &c1, &x2, &c2, &x3, &c3);
		closure(x1, c1 == 'R', x2, c2 == 'R');
		closure(x1, c1 == 'R', x3, c3 == 'R');
		closure(x2, c2 == 'R', x3, c3 == 'R');
	}
	get_SCC(2 * n + 2);

	ok = get_result(n + 1);

	if (ok){
		for (int i = 1; i <= n; i++){
			if (result[2 * i + 1] == 1){
				printf("R");
			}
			else printf("B");
		}
		printf("\n");
	}
	else printf("-1\n");
	return 0;
}
