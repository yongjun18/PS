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
const ll INF = 1e15;
const int MOD = 1e9 + 7;

struct Edge{ 
	int next;
	ll w;
};
struct QNode{
	int from, now;
	ll wsum;
	bool operator <(const QNode& rhs) const { 
		return wsum > rhs.wsum; 
	}
};

vector<Edge> adj[100100];
vector<ll> dist;
vector<int> ansv;

void dijkstra(int n, int k){
	dist = vector<ll>(n + 1, INF);
	ansv = vector<int>(n + 1, 0);
	priority_queue<QNode> pq;

	for (int i = 0; i < k; i++){
		int x; 
		scanf("%d", &x);
		dist[x] = 0;
		ansv[x] = x;
		pq.push({ x, x, 0 });
	}

	while (pq.size()){
		int from = pq.top().from;
		int now = pq.top().now;
		ll wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]){
			int next = e.next;
			ll next_dist = wsum + e.w;
			if (dist[next] > next_dist){
				dist[next] = next_dist;
				ansv[next] = from;
				pq.push({ from, next, next_dist });
			}
			else if (dist[next] == next_dist && ansv[next] > from){
				ansv[next] = from;
				pq.push({ from, next, next_dist });
			}
		}
	}
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m, k;
		ll dsum, vsum;

		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < n + 5; i++){
			adj[i].clear();
		}

		while (m--){
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			adj[u].push_back({ v, w });
			adj[v].push_back({ u, w });
		}

		dijkstra(n, k);

		dsum = vsum = 0;
		for (int i = 1; i <= n; i++){
			dsum += dist[i];
			vsum += ansv[i];
		}

		printf("Case #%d\n", test);
		printf("%lld\n", dsum);
		printf("%lld\n", vsum);
	}

	return 0;
}
