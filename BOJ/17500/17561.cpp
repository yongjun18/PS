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

const int MX = 100100;

ll tree[4 * MX];

ll build(int no, int nl, int nr) {
	if (nl + 1 == nr) return tree[no] = INF;
	int mid = (nl + nr) / 2;
	return tree[no] = min(build(2 * no, nl, mid), build(2 * no + 1, mid, nr));
}
ll build(int n = MX) { return build(1, 0, n); }
ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return INF;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return min(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = min(tree[no], val);
	int mid = (nl + nr) / 2;
	return tree[no] = min(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }

struct Edge{ int next, w; };
struct QNode{
	int now, wsum;
	bool operator <(const QNode& rhs) const { return wsum > rhs.wsum; }
};

vector<Edge> adj[MX];

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

struct Node{
	int a, b, c, useful;
	bool operator < (const Node& rhs) const{
		return a < rhs.a;
	}
};
vector<Node> nds;
vector< vector<Node> > nds2;

void compress(int n){
	vector<int> used;
	for (int i = 0; i < n; i++){
		used.push_back(nds[i].b);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < n; i++){
		nds[i].b = lower_bound(used.begin(), used.end(), nds[i].b) - used.begin();
	}
}

int main()
{
	int n, m;
	int ans;

	scanf("%d %d", &n, &m);
	while (m--){
		int a, b, w;
		scanf("%d %d %d", &a, &b, &w);
		add_edge(a, b, w);
		add_edge(b, a, w);
	}

	nds = vector<Node>(n);
	for (int i = 0; i < n; i++){
		nds[i].useful = 1;
	}

	dijkstra(n, 0);
	for (int i = 0; i < n; i++){
		nds[i].a = dist[i];
	}
	dijkstra(n, 1);
	for (int i = 0; i < n; i++){
		nds[i].b = dist[i];
	}
	dijkstra(n, 2);
	for (int i = 0; i < n; i++){
		nds[i].c = dist[i];
	}
	compress(n);
	sort(nds.begin(), nds.end());

	nds2.push_back(vector<Node>());
	nds2[0].push_back(nds[0]);
	for (int i = 1; i < nds.size(); i++){
		if (nds2.back().back().a < nds[i].a){
			nds2.push_back(vector<Node>());
		}
		nds2.back().push_back(nds[i]);
	}

	build();
	for (auto& v : nds2){
		for (Node& it : v){
			if (query(0, it.b + 1) <= it.c){
				it.useful = 0;
			}
		}
		for (Node& it : v){
			update(it.b, it.c);
		}
		for (Node& it : v){
			if (query(0, it.b) <= it.c){
				it.useful = 0;
			}
			if (query(0, it.b + 1) < it.c){
				it.useful = 0;
			}
		}
	}

	ans = 0;
	for (auto& v : nds2){
		for (Node& it : v){
			ans += it.useful;
		}
	}
	printf("%d\n", ans);
	return 0;
}
