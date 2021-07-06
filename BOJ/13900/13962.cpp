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
ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return 0;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return query(l, r, 2 * no, nl, mid) + query(l, r, 2 * no + 1, mid, nr);
}
ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] = val;
	int mid = (nl + nr) / 2;
	return tree[no] = update(idx, val, 2 * no, nl, mid) + update(idx, val, 2 * no + 1, mid, nr);
}
ll update(int idx, ll val, int n = MX) { return update(idx, val, 1, 0, n); }

struct Emp{
	int num;
	ll tim;
	int rak;
	bool operator < (const Emp& rhs) const{
		return rak < rhs.rak;
	}
};
vector<Emp> emps;
vector<int> adj[100100];
int pcnt = 0;
int pos[100100];
int posmax[100100];
ll ans[100100];

int dfs(int now){
	pos[now] = pcnt++;
	posmax[now] = pos[now];
	for (int nxt : adj[now]){
		posmax[now] = max(posmax[now], dfs(nxt));
	}
	return posmax[now];
}

int main()
{
	int n;
	int root, nxtupd;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++){
		int m, r;
		ll t;
		scanf("%d %d %lld", &m, &r, &t);
		emps.push_back({ i, t, r });

		if (m != -1) adj[m].push_back(i);
		else root = i;
	}
	dfs(root);

	sort(emps.begin(), emps.end());
	nxtupd = 0;
	for (int i = 0; i < emps.size(); i++){
		while (nxtupd < i && emps[nxtupd].rak < emps[i].rak){
			int num = emps[nxtupd].num;
			ll tim = emps[nxtupd].tim;
			update(pos[num], tim);
			nxtupd++;
		}
		int inum = emps[i].num;
		ans[inum] = query(pos[inum], posmax[inum] + 1);
	}
	for (int i = 1; i <= n; i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
