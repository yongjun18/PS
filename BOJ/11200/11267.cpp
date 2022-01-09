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

vector<int> adj[100100];
int vis1[100100];
int vis2[100100];
vector<int> diameter;

int bfs(int v, int vis[]) {
	vector<int> vec1, vec2;
	int last = v;

	vis[v] = 0;
	vec1.push_back(v);

	while (vec1.size() > 0) {
		for (int it : vec1) {
			for (int nxt : adj[it]) {
				if (vis[nxt] != -1) continue;
				vis[nxt] = vis[it] + 1;
				vec2.push_back(nxt);
				last = nxt;
			}
		}
		swap(vec1, vec2);
		vec2.clear();
	}
	return last;
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	memset(vis1, -1, sizeof(vis1));
	memset(vis2, -1, sizeof(vis2));

	for (int i = 0; i < n; i++) {
		if (vis1[i] == -1) {
			int v1 = bfs(i, vis1);
			int v2 = bfs(v1, vis2);
			diameter.push_back(vis2[v2]);
		}
	}

	sort(diameter.begin(), diameter.end());

	while (diameter.size() >= 2) {
		int d1, d2, newd;
		d1 = diameter.back();
		diameter.pop_back();
		d2 = diameter.back();
		diameter.pop_back();

		newd = max(d1, (d1 + 1) / 2 + (d2 + 1) / 2 + 1);
		diameter.push_back(newd);
	}
	printf("%d\n", diameter.back());
	return 0;
}
