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

int arr[400100];
vector<int> adj[400100];
vector<int> order;

int topological_sort(int n) {
	vector<int> indegree(n + 1, 0);
	priority_queue< pair<int, int> > que;
	order.clear();

	for (int i = 1; i <= n; i++) {
		for (int next : adj[i])
			indegree[next]++;
	}

	for (int i = 1; i <= n; i++) {
		if (indegree[i] == 0) que.push({ -arr[i], i });
	}

	for (int t = 0; t < n; t++) {
		if (que.empty()) break;
		int now = que.top().second;
		que.pop();

		order.push_back(now);
		for (int next : adj[now]) {
			indegree[next]--;
			if (indegree[next] == 0) que.push({ -arr[next], next });
		}
	}
	return (order.size() == n);
}

int main()
{
	int n;
	int maxv;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		int d;
		scanf("%d", &arr[i]);
		scanf("%d", &d);
		while (d--){
			int x;
			scanf("%d", &x);
			adj[i].push_back(x);
		}
	}

	topological_sort(n);
	reverse(order.begin(), order.end());

	maxv = 0;
	for (int i = 0; i < n; i++){
		maxv = max(maxv, i + arr[order[i]]);
	}
	printf("%d\n", maxv);
	return 0;
}
