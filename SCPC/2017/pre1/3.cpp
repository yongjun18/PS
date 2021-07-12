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

const int MX = 40100;
vector<int> adj[MX];
vector< vector<int> > SCC;

int dfsn[MX];
int visit[MX];
int finish[MX];
int cnt = 0;
stack<int> st;
int snum[MX];
int scnt = 0;
int result[MX];

int dfs(int x) {
	visit[x] = 1;
	dfsn[x] = cnt++;
	st.push(x);

	int minv = dfsn[x];
	for (int next : adj[x]) {
		if (!visit[next]) minv = min(minv, dfs(next));
		else if (!finish[next]) minv = min(minv, dfsn[next]);
	}

	if (minv == dfsn[x]) {
		vector<int> now_scc;
		while (1) {
			int top = st.top(); st.pop();
			snum[top] = scnt;

			now_scc.push_back(top);
			finish[top] = 1;
			if (top == x) break;
		}
		SCC.push_back(now_scc);
		scnt++;
	}
	return minv;
}

int get_SCC(int n) {
	for (int i = 0; i < n; i++) {
		if (!visit[i]) dfs(i);
	}
	return SCC.size();
}

void closure(int x, int xbool, int y, int ybool) {
	adj[x * 2 + !xbool].push_back(y * 2 + ybool);
	adj[y * 2 + !ybool].push_back(x * 2 + xbool);
}

int get_result(int n) {
	for (int i = 0; i < n; i++) {
		if (snum[2 * i] == snum[2 * i + 1])
			return 0;
	}

	for (int i = 0; i < 2 * n; i++){
		result[i] = -1;
	}
	for (int i = scnt - 1; i >= 0; i--) {
		for (int now : SCC[i]) {
			if (result[now] != -1) continue;
			result[now] = 0;
			result[now ^ 1] = 1;
		}
	}
	return 1;
}

map<string, int> mp;
string sname[MX];

void init(int n, int m){
	cnt = 0;
	scnt = 0;
	while (st.size()) st.pop();
	SCC.clear();
	for (int i = 0; i < n * m * 4 + 5; i++){
		visit[i] = 0;
		finish[i] = 0;
		adj[i].clear();
	}
	mp.clear();
}

string get_name(char c, int idx, int num){
	string ret;
	ret += c;
	ret += '0' + (idx / 10);
	ret += '0' + (idx % 10);
	ret += '0' + (num / 10);
	ret += '0' + (num % 10);
	return ret;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		int res;

		scanf("%d %d", &n, &m);
		init(n, m);

		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				int t, a, b;
				string sn1, sn2;
				scanf("%d %d %d", &t, &a, &b);
				sn1 = get_name('R', i, a);
				sn2 = get_name('C', j, b);

				if (mp.find(sn1) == mp.end()){
					sname[mp.size()] = sn1;
					mp[sn1] = mp.size();
				}
				if (mp.find(sn2) == mp.end()){
					sname[mp.size()] = sn2;
					mp[sn2] = mp.size();
				}
				if (t == 0){
					closure(mp[sn1], 0, mp[sn2], 0);
					closure(mp[sn1], 1, mp[sn2], 1);
				}
				else{
					closure(mp[sn1], 0, mp[sn2], 1);
					closure(mp[sn1], 1, mp[sn2], 0);
				}
			}
		}

		get_SCC(2 * mp.size());
		res = get_result(mp.size());

		printf("Case #%d\n", test);	
		if (res == 0) printf("Impossible\n");
		else{
			for (int i = 0; i < mp.size(); i++){
				if (result[i * 2 + 1] == 1){
					printf("%s ", sname[i].c_str());
				}
			}
			printf("\n");
		}
	}

	return 0;
}
