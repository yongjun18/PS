#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

vector<int> adj[200100];
int ans[200100];
int believe[200100];
int near[200100];
queue<int> que;

int main()
{
	int n, m;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		while (1){
			int x;
			scanf("%d", &x);
			if (x == 0) break;
			adj[i].push_back(x);
		}
	}

	memset(ans, -1, sizeof(ans));
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int x;
		scanf("%d", &x);
		ans[x] = 0;
		believe[x] = 1;
		que.push(x);
	}

	while (que.size()){
		int now = que.front(); 
		que.pop();

		for (int nxt : adj[now]){
			if (believe[nxt]) continue;
			near[nxt]++;
			if (near[nxt] >= (adj[nxt].size() + 1) / 2){
				believe[nxt] = 1;
				ans[nxt] = ans[now] + 1;
				que.push(nxt);
			}
		}
	}
	
	for (int i = 1; i <= n; i++){
		printf("%d ", ans[i]);
	}
	printf("\n");
	return 0;
}
