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

map<string, int> mp;
vector<int> adj[200];
vector<int> order;
double val[200];

char str[15];

int tsort(int n) {
	vector<int> indegree(n, 0);
	queue<int> que;
	order.clear();

	for (int i = 0; i < n; i++) {
		for (int next : adj[i])
			indegree[next]++;
	}

	for (int i = 0; i < n; i++) {
		if (indegree[i] == 0) que.push(i);
	}

	for (int t = 0; t < n; t++) {
		if (que.empty()) break;
		int now = que.front(); que.pop();

		order.push_back(now);
		for (int next : adj[now]) {
			indegree[next]--;
			if (indegree[next] == 0) que.push(next);
		}
	}
	return (order.size() == n);
}

int get_num(char *s) {
	int res;
	auto it = mp.find(s);

	if (it == mp.end()) {
		res = mp.size();
		mp[s] = mp.size();
	}
	else res = it->second;

	return res;
}

int main()
{
	int n, m;
	string ans;
	double maxv;
	
	scanf("%d %d", &n, &m);
	scanf("%s", str);
	mp[str] = 0;

	for (int i = 0; i < n; i++) {
		int son, par1, par2;

		scanf("%s", str);
		son = get_num(str);
		scanf("%s", str);
		par1 = get_num(str);
		scanf("%s", str);
		par2 = get_num(str);

		adj[par1].push_back(son);
		adj[par2].push_back(son);
	}

	tsort(mp.size());
	val[0] = 1.0;
	for (int it : order) {
		for (int nxt : adj[it]) {
			val[nxt] += val[it] / 2;
		}
	}

	maxv = 0;
	while (m--) {
		int num;
		scanf("%s", str);
		num = get_num(str);
		if (maxv < val[num]) {
			ans = str;
			maxv = val[num];
		}
	}
	printf("%s\n", ans.c_str());
	return 0;
}
