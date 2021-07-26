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

vector<int> adj[300100];
int cnt1[300100];
int cnt2[300100];
int cnt3[300100];

void dfs(int now, int p){
	for (int nxt : adj[now]){
		if (nxt == p) continue;
		dfs(nxt, now);
		cnt1[now]++;
		cnt2[now] += cnt1[nxt];
		cnt3[now] += cnt2[nxt];
	}
}

int main()
{
	int n;
	ll dcnt, gcnt;

	scanf("%d", &n);

	for (int i = 0; i < n - 1; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1, -1);

	dcnt = gcnt = 0;
	for (int i = 1; i <= n; i++){
		dcnt += cnt3[i];
		dcnt += (ll)cnt2[i] * (cnt1[i] - 1);

		gcnt += (ll)cnt1[i] * (cnt1[i] - 1) * (cnt1[i] - 2) / 6;
		if (i > 1){
			gcnt += (ll)cnt1[i] * (cnt1[i] - 1) / 2;
		}
	}

	if (dcnt > gcnt * 3) printf("D\n");
	else if (dcnt < gcnt * 3) printf("G\n");
	else printf("DUDUDUNGA\n");

	return 0;
}
