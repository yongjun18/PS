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

int n, k;
vector<int> adj[100100];
int apt[100100];
int cnt[100100];

int dfs(int now, int h){
	int ret = 0;
	int foundK = 0;
	cnt[now] = apt[now];

	for (int nxt : adj[now]){
		if (nxt == h) continue;

		ret += dfs(nxt, now);
		cnt[now] += cnt[nxt];
		if (cnt[nxt] == k){
			foundK = 1;
		}
	}
	if (cnt[now] == 0 || foundK == 1){
		ret++;
	}
	return ret;
}

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n - 1; i++){
		int x, y;
		scanf("%d %d %*d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	for (int i = 0; i < k; i++){
		int x;
		scanf("%d", &x);
		apt[x] = 1;
	}

	printf("%d\n", n - dfs(1, 1));

	return 0;
}
