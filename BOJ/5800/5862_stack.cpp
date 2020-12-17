#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
ll l;
vector< pair<int, ll> > adj[200100];
int siz[200100];

ll dist[200100];

int check[200100];

int stk[200100];
ll stkd[200100];
int ssiz = 0;

int exc[200100];
int ans[200100];

void dfs(int now){
	siz[now] = 1;

	for (auto it : adj[now]){
		int nxt = it.first;
		dist[nxt] = dist[now] + it.second;
		dfs(nxt);
		siz[now] += siz[nxt];
	}
}

ll parametric_search(ll x, ll y, int now){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (dist[now] - dist[stk[mid]] <= l) hi = mid;
		else lo = mid;
	}
	return hi;
}

void dfs2(int now){
	stk[ssiz] = now;
	stkd[ssiz] = dist[now];
	ssiz++;

	int pos = parametric_search(0, ssiz - 1, now);
	if (pos > 0){
		check[stk[pos - 1]]++;
	}
	for (auto it : adj[now]){
		dfs2(it.first);
	}

	ssiz--;
}

void dfs3(int now){
	exc[now] = check[now];

	for (auto it : adj[now]){
		int nxt = it.first;
		dfs3(nxt);
		exc[now] += exc[nxt];
	}
}


int main()
{	
	scanf("%d %lld", &n, &l);

	for (int i = 2; i <= n; i++){
		int p;
		ll x;
		scanf("%d %lld", &p, &x);
		adj[p].push_back({ i, x });
	}

	dfs(1);
	dfs2(1);
	dfs3(1);

	for (int i = 1; i <= n; i++){
		printf("%d\n", siz[i] - exc[i]);
	}
	return 0;
}
