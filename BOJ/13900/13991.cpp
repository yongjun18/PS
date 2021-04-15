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
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int BRD = -1;
struct Edge{
	int nxt;
	int type;
};
vector<Edge> adj[50010];
int visit[50010];
int depth[50010];
vector<Edge*> st;

vector< vector<int> > cycles;
int cnum = 0;
int check[50010];

char buf[105];
vector<string> ans;

void dfs1(int x, int h){
	for (auto &it : adj[x]){
		if (it.nxt == h) continue;
		if (visit[it.nxt] && depth[it.nxt] < depth[x]){
			int diff = depth[x] - depth[it.nxt];
			vector<int> nowc;
			cnum++;
			it.type = cnum;
			nowc.push_back(it.nxt);
			for (int i = 0; i < diff; i++){
				Edge* e = *(st.rbegin() + i);
				e->type = cnum;
				nowc.push_back(e->nxt);
			}
			cycles.push_back(nowc);
			continue;
		}
		if (visit[it.nxt]) continue;

		it.type = BRD;
		depth[it.nxt] = depth[x] + 1;
		visit[it.nxt] = 1;
		st.push_back(&it);
		dfs1(it.nxt, x);

		st.pop_back();
	}
}

void make_cycle(int ci, int h){
	int idx, siz;
	vector<int> order;
	
	order.push_back(h);
	idx = 0;
	siz = cycles[ci].size();
	while (cycles[ci][idx] != h) idx++;
	for (int i = 1; i < siz; i++){
		order.push_back(cycles[ci][(idx + i) % siz]);
	}

	sprintf(buf, "r %d 1 4\n", h); ans.push_back(buf);
	for (int i = 1; i < siz; i++){
		sprintf(buf, "r %d 1 3\n", order[i]); ans.push_back(buf);
		sprintf(buf, "j %d %d\n", h, order[i]); ans.push_back(buf);
		if (i == 1) {
			sprintf(buf, "c %d 4 3\n", h); ans.push_back(buf);
		}
		else{
			sprintf(buf, "c %d 1 3\n", h); ans.push_back(buf);
		}
		sprintf(buf, "r %d 1 2\n", h); ans.push_back(buf);
		sprintf(buf, "r %d 3 1\n", h); ans.push_back(buf);
	}
	sprintf(buf, "c %d 1 4\n", h); ans.push_back(buf);
	sprintf(buf, "r %d 1 2\n", h); ans.push_back(buf);
	sprintf(buf, "r %d 4 1\n", h); ans.push_back(buf);
}

void make_brd(int h, int nxt){
	sprintf(buf, "r %d 1 3\n", nxt); ans.push_back(buf);
	sprintf(buf, "j %d %d\n", h, nxt); ans.push_back(buf);
	sprintf(buf, "c %d 1 3\n", h); ans.push_back(buf);
	sprintf(buf, "r %d 3 2\n", h); ans.push_back(buf);
}

void dfs2(int x){
	for (auto it : adj[x]){
		if (it.type > 0){
			if (check[it.type]) continue;
			
			check[it.type] = 1;
			for (int mem : cycles[it.type - 1]){
				if (mem == x) continue;
				dfs2(mem);
			}
			make_cycle(it.type - 1, x);
		}
		if (it.type == BRD){
			dfs2(it.nxt);
			make_brd(x, it.nxt);
		}
	}
}

int main()
{
	int n, m;
	
	scanf("%d %d", &n, &m);
	while (m--){
		int k;
		int pv = -1;
		scanf("%d", &k);
		for (int i = 0; i < k; i++){
			int x;
			scanf("%d", &x);
			if (pv != -1){
				adj[x].push_back({ pv, 0 });
				adj[pv].push_back({ x, 0 });
			}
			pv = x;
		}
	}
	visit[1] = 1;
	dfs1(1, -1);
	dfs2(1);

	printf("%d\n", ans.size());
	for (auto it : ans){
		printf("%s", it.c_str());
	}
	return 0;
}
