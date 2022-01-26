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

vector<int> horror;
vector<int> adj[1010];
int dist[1010];
queue<int> que;

int main()
{
	int n, h, l;
	int ans, maxv;

	scanf("%d %d %d", &n, &h, &l);
	for (int i = 0; i < h; i++) {
		int x;
		scanf("%d", &x);
		horror.push_back(x);
	}
	while (l--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (int i = 0; i < n; i++) {
		dist[i] = INF;
	}
	for (int it : horror) {
		dist[it] = 0;
		que.push(it);
	}

	while (que.size()) {
		int now = que.front(); que.pop();
		for (int nxt : adj[now]) {
			if (dist[nxt] < INF) continue;
			dist[nxt] = dist[now] + 1;
			que.push(nxt);
		}
	}

	ans = -1;
	maxv = -1;
	for (int i = 0; i < n; i++) {
		if (maxv < dist[i]) {
			maxv = dist[i];
			ans = i;
		}
	}
	printf("%d\n", ans);
	return 0;
}
