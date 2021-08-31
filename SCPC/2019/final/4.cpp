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

const int MX = 1010;
int mx, s, t;

struct Edge {
	int from, to;
	ll capacity, flow, cost;
	Edge* reverse;
};
vector<Edge*> adj[MX];

void add_edge(int u, int v, ll cp, ll co) {
	Edge* ef = new Edge();
	Edge* er = new Edge();
	*ef = { u, v, cp, 0, co, er };
	*er = { v, u, 0, 0, -co, ef };
	adj[u].push_back(ef);
	adj[v].push_back(er);
}

ll total_flow;
ll total_cost;
ll MCMF(int n, int source, int sink) {
	total_flow = 0;
	total_cost = 0;

	while (1) {
		vector<Edge*> prev(n, NULL);
		vector<ll> dist(n, INF);
		vector<int> inque(n, 0);
		queue<int> q;

		q.push(source); inque[source] = 1;
		dist[source] = 0;

		while (!q.empty()) {
			int now = q.front(); q.pop(); inque[now] = 0;
			for (Edge* e : adj[now]) {
				if (e->capacity - e->flow > 0 && dist[now] + e->cost < dist[e->to]) {
					dist[e->to] = dist[now] + e->cost;
					prev[e->to] = e;

					if (!inque[e->to]) {
						q.push(e->to); inque[e->to] = 1;
					}
				}
			}
		}

		if (prev[sink] == NULL) break;

		ll amount = INF;
		for (int p = sink; p != source; p = prev[p]->from)
			amount = min(amount, prev[p]->capacity - prev[p]->flow);

		for (int p = sink; p != source; p = prev[p]->from) {
			total_cost += amount * prev[p]->cost;
			prev[p]->flow += amount;
			prev[p]->reverse->flow -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}

ll arr[MX];

int main()
{
	int tc;

	scanf("%d", &tc);

	for (int test = 1; test <= tc; test++){
		int n;
		ll r, l;

		scanf("%d %lld %lld", &n, &r, &l);
		for (int i = 0; i < n; i++){
			scanf("%lld", &arr[i]);
		}
		sort(arr, arr + n);

		s = n + 2;
		t = n + 3;
		mx = n + 5;
		for (int i = 0; i < mx; i++){
			adj[i].clear();
		}

		if (arr[0] - r < 0) add_edge(s, 0, r - arr[0], 0);
		if (arr[0] - r > 0) add_edge(0, t, arr[0] - r, 0);

		if (arr[n - 1] + r > l) add_edge(s, n, arr[n - 1] + r - l, 0);
		if (arr[n - 1] + r < l) add_edge(n, t, l - arr[n - 1] - r, 0);

		for (int i = 0; i + 1 < n; i++){
			ll r1 = arr[i] + r;
			ll l2 = arr[i + 1] - r;
			if (r1 < l2) add_edge(i + 1, t, l2 - r1, 0);
			if (r1 > l2) add_edge(s, i + 1, r1 - l2, 0);
		}

		for (int i = 0; i + 1 <= n; i++){
			add_edge(i, i + 1, INF, 1);
			add_edge(i + 1, i, INF, 1);
		}

		MCMF(mx, s, t);

		printf("Case #%d\n", test);
		printf("%lld\n", total_cost);
	}

	return 0;
}
