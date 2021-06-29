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

set<int> adj[110];
int del[105];
queue<int> que;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int k, l, n, m;
		int nown;
		int ans;

		scanf("%d %d %d %d", &k, &l, &n, &m);
		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
			del[i] = 0;
		}
		while (que.size()) que.pop();
		ans = 0;

		while (m--){
			int u, v;
			scanf("%d %d", &u, &v);
			adj[u].insert(v);
			adj[v].insert(u);
		}

		for (int i = 1; i <= n; i++){
			if (adj[i].size() < k){
				que.push(i);
				del[i] = 1;
				ans += i;
			}
			else if (n - 1 - adj[i].size() < l){
				que.push(i);
				del[i] = 1;
				ans += i;
			}
		}

		nown = n;
		while (que.size()){
			int now = que.front();
			que.pop();
			for (int nxt : adj[now]){
				adj[nxt].erase(now);
			}
			nown--;

			for (int i = 1; i <= n; i++){
				if (del[i] == 1) continue;
				if (adj[i].size() < k){
					que.push(i);
					del[i] = 1;
					ans += i;
				}
				else if (nown - 1 - adj[i].size() < l){
					que.push(i);
					del[i] = 1;
					ans += i;
				}
			}
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
