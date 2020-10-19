#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Edge{ int next, w; };
struct QNode{
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[1000100];

void add_edge(int u, int v, int w){
	adj[u].push_back({v, w});
}

vector<int> dist;

void dijkstra(int n, int start){
	dist = vector<int>(n, INF);
	dist[start] = 0;
	priority_queue<QNode> pq;
	pq.push({start, 0});

	while(pq.size()){
		int now = pq.top().now;
		int wsum = pq.top().wsum;
		pq.pop();

		if(dist[now] < wsum) continue;

		for(Edge e : adj[now]){
			int next = e.next;
			int next_dist = wsum + e.w;
			if(dist[next] > next_dist){
				dist[next] = next_dist;
				pq.push({next, next_dist});
			}
		}
	}
}

int arr[1010][1010];
int num[1010][1010];

int main()
{
	int n, m;
	int cnt = 0;
	int ans;

	scanf("%d %d", &n, &m);

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf("%d", &arr[i][j]);
			num[i][j] = cnt++;
			if(arr[i][j] == -1){
				arr[i][j] = INF;
			}
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(j+1 < m){
				add_edge(num[i][j], num[i][j+1], arr[i][j+1]);
				add_edge(num[i][j+1], num[i][j], arr[i][j]);
			}
			if(i+1 < n){
				add_edge(num[i][j], num[i+1][j], arr[i+1][j]);
				add_edge(num[i+1][j], num[i][j], arr[i][j]);
			}
		}
	}
	dijkstra(n*m, num[0][0]);

	ans = dist[num[n-1][m-1]] + arr[0][0];
	if(ans >= INF)
		printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}
