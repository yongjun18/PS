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

struct Edge{ int next, w; };
struct QNode{
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[20100];

void add_edge(int u, int v, int w){
	adj[u].push_back({ v, w });
}

vector<int> dist;

void dijkstra(int n, int start){
	dist = vector<int>(n, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({ start, 0 });

	while (pq.size()){
		int now = pq.top().now;
		int wsum = pq.top().wsum;
		pq.pop();

		if (dist[now] < wsum) continue;

		for (Edge e : adj[now]){
			int next = e.next;
			int next_dist = wsum + e.w;
			if (dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({ next, next_dist });
			}
		}
	}
}

vector<int> want;
int distc[20][20];
int dp[1 << 16][16][2];

int main()
{
	int n, p, m, g, t;
	int res1, res2;

	scanf("%d %d %d %d %d", &n, &p, &m, &g, &t);
	
	want.push_back(0);
	for (int i = 0; i < p; i++){
		int pi, ti;
		scanf("%d %d", &pi, &ti);
		want.push_back(pi);
		g -= ti;
	}

	while (m--){
		int si, di, ti;
		scanf("%d %d %d", &si, &di, &ti);
		add_edge(si, di, ti);
		add_edge(di, si, ti);
	}

	for (int i = 0; i < want.size(); i++){
		dijkstra(n, want[i]);
		for (int j = 0; j < want.size(); j++){
			distc[i][j] = distc[j][i] = dist[want[j]];
		}
	}

	for (int mask = 0; mask < (1 << want.size()); mask++){
		for (int last = 0; last < want.size(); last++){
			for (int used = 0; used < 2; used++){
				dp[mask][last][used] = INF;
			}
		}
	}
	dp[1][0][0] = 0;
	for (int mask = 0; mask < (1 << want.size()); mask++){
		for (int last = 0; last < want.size(); last++){
			for (int used = 0; used < 2; used++){
				if (dp[mask][last][used] >= INF) continue;

				for (int nxt = 0; nxt < want.size(); nxt++){
					if ((1 << nxt) & mask) continue;

					int nmask = mask + (1 << nxt);
					dp[nmask][nxt][used] = min(dp[nmask][nxt][used], dp[mask][last][used] + distc[last][nxt]);

					if (used == 0){
						dp[nmask][nxt][1] = min(dp[nmask][nxt][1], dp[mask][last][used] + t);
					}
				}
			}
		}
	}

	res1 = res2 = INF;
	for (int last = 0; last < want.size(); last++){
		int mask = (1 << want.size()) - 1;
		res1 = min(res1, dp[mask][last][0] + distc[last][0]);
		res2 = min(res2, dp[mask][last][1] + distc[last][0]);
		res2 = min(res2, dp[mask][last][0] + t);
	}

	if (res1 > g && res2 > g){
		printf("impossible\n");
	}
	else if (res1 <= g){
		printf("possible without taxi\n");
	}
	else{
		printf("possible with taxi\n");
	}

	return 0;
}
