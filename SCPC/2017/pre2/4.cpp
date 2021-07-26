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

set< pair<ll, int> > adj[100100];
ll maxv[100100];
priority_queue< pair<ll, int> > pq;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, p;
		int nowcnt;
		ll ans;

		scanf("%d", &n);
		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
			maxv[i] = 0;
		}
		while (pq.size()) pq.pop();

		for (int i = 0; i < n - 1; i++){
			int u, v;
			ll w;
			scanf("%d %d %lld", &u, &v, &w);
			adj[u].insert({ v, w });
			adj[v].insert({ u, w });
		}
		scanf("%d", &p);

		for (int i = 1; i <= n; i++){
			if (adj[i].size() == 1){
				ll w = adj[i].begin()->second;
				pq.push({ -w, i });
			}
		}
		nowcnt = n;

		while (nowcnt > p){
			ll wsum = -pq.top().first;
			int now = pq.top().second;
			pq.pop();

			int nxt = adj[now].begin()->first;
			ll w = adj[now].begin()->second;
			maxv[nxt] = max(maxv[nxt], wsum);

			adj[now].erase({ nxt, w });
			adj[nxt].erase({ now, w });
			if (adj[nxt].size() == 1){
				ll nwsum = maxv[nxt] + adj[nxt].begin()->second;
				pq.push({ -nwsum, nxt });
			}
			nowcnt--;
		}

		ans = 0;
		for (int i = 1; i <= n; i++){
			ans = max(ans, maxv[i]);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
