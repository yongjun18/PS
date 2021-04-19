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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

vector<int> adj[100100];
int ind[100100];
int outd[100100];

vector<int> spc;
int is_spc[100100];
int idx[100100];
vector<int> sadj[50];
set< pair<int, int> > st;
vector<int> ords[50][50];

int build_ords(int from, int now){
	if (is_spc[now]) return idx[now];

	int to = build_ords(from, adj[now][0]);
	ords[from][to].push_back(now);
	return to;
}

vector<int> ans;
int visit[50];
int dfs(int now, int depth){
	if (depth == (int)spc.size() - 1){
		for (int i = 0; i < sadj[now].size(); i++){
			if (sadj[now][i] == 0){
				ans.push_back(1);
				for (int j = (int)ords[now][i].size() - 1; j >= 0; j--){
					ans.push_back(ords[now][i][j]);
				}
				ans.push_back(spc[now]);
				return 1;
			}
		}
		return 0;
	}

	for (int nxt : sadj[now]){
		if (visit[nxt]) continue;

		visit[nxt] = 1;
		if (dfs(nxt, depth + 1)){
			for (int i = (int)ords[now][nxt].size() - 1; i >= 0; i--){
				ans.push_back(ords[now][nxt][i]);
			}
			ans.push_back(spc[now]);
			return 1;
		}
		visit[nxt] = 0;
	}
	return 0;
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	while (m--){
		int x, y;
		scanf("%d %d", &x, &y);
		if (x == y) continue;
		
		adj[x].push_back(y);
		outd[x]++;
		ind[y]++;
	}

	for (int i = 1; i <= n; i++){
		if (ind[i] == 0 || outd[i] == 0){
			printf("There is no route, Karl!\n");
			return 0;
		}
	}

	spc.push_back(1);
	idx[1] = 0;
	is_spc[1] = 1;
	for (int i = 2; i <= n; i++){
		if (ind[i] > 1 || outd[i] > 1){
			spc.push_back(i);
			idx[i] = (int)spc.size() - 1;
			is_spc[i] = 1;
		}
	}

	for (int i = 0; i < spc.size(); i++){
		int v = spc[i];
		int ordcnt = 0;
		for (int j = 0; j < adj[v].size(); j++){
			if (is_spc[adj[v][j]] == 0){
				ordcnt++;
			}
		}

		if (ordcnt == 0){
			for (int j = 0; j < adj[v].size(); j++){
				int nxt = adj[v][j];
				if (st.find({ i, idx[nxt] }) == st.end()){
					sadj[i].push_back(idx[nxt]);
					st.insert({ i, idx[nxt] });
				}
			}
		}
		if (ordcnt == 1){
			for (int j = 0; j < adj[v].size(); j++){
				int nxt = adj[v][j];
				if (is_spc[nxt] == 0){
					int to = build_ords(i, nxt);
					sadj[i].push_back(to);
					reverse(ords[i][to].begin(), ords[i][to].end());
					break;
				}
			}
		}
		if (ordcnt >= 2){
			printf("There is no route, Karl!\n");
			return 0;
		}
	}

	visit[0] = 1;
	dfs(0, 0);

	if (ans.size() == n + 1){
		reverse(ans.begin(), ans.end());
		for (int it : ans){
			printf("%d ", it);
		}
		printf("\n");
	}
	else{
		printf("There is no route, Karl!\n");
	}

	return 0;
}
