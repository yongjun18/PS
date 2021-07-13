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
	int now;
	ll wsum;
	int from;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

int n, m;
ll arr[510][510];
int num[510][510];
int visit[250100];
vector<Edge> adj[250100];
int from[250100];
int ans[510];

void add_edge(int u, int v, ll w){
	adj[u].push_back({ v, w });
}

vector<ll> dist;

void dijkstra(int mx){
	priority_queue<QNode> pq;
	dist = vector<ll>(mx, INF);
	for (int i = 0; i < n; i++){
		dist[num[i][m - 1]] = 0;
		pq.push({ num[i][m - 1], 0, i });
	}

	while (pq.size()){
		int now = pq.top().now;
		ll wsum = pq.top().wsum;
		int f = pq.top().from;
		pq.pop();

		if (dist[now] < wsum) continue;
		from[now] = f;

		for (Edge e : adj[now]){
			int next = e.next;
			ll next_dist = wsum + e.w;
			if (dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({ next, next_dist, f });
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			scanf("%lld", &arr[i][j]);
			num[i][j] = i * m + j;
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m - 1; j++){
			add_edge(num[i][j], num[i][j + 1], arr[i][j]);
			add_edge(num[i][j + 1], num[i][j], arr[i][j + 1]);
		}
	}
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < m; j++){
			add_edge(num[i][j], num[i + 1][j], arr[i][j]);
			add_edge(num[i + 1][j], num[i][j], arr[i + 1][j]);
		}
	}
	dijkstra(n * m);

	for (int i = 0; i < n; i++){
		int now = num[i][0];
		ans[from[now]]++;
	}
	for (int i = 0; i < n; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
