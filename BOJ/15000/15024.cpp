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

char name[505][10];
map<string, int> mp;
char buf[10];
vector<int> adj[505];

int visit[505];
int pv[505];

int ans;
vector<int> ansv;
void bfs(int start){
	vector<int> v1, v2;

	memset(visit, 0, sizeof(visit));
	visit[start] = 1;
	v1.push_back(start);

	for (int t = 1; t < ans; t++){
		for (int now : v1){
			for (int nxt : adj[now]){
				if (nxt == start){
					ans = t;
					ansv.clear();
					int it = now;
					while (1){
						ansv.push_back(it);
						if (it == start) break;
						it = pv[it];
					}
					reverse(ansv.begin(), ansv.end());
					return;
				}
				if (visit[nxt] == 0){
					visit[nxt] = 1;
					v2.push_back(nxt);
					pv[nxt] = now;
				}
			}
		}
		swap(v1, v2);
		v2.clear();
		if (v1.size() == 0) break;
	}
}

int main()
{
	int n;

	scanf("%d", &n);

	for (int i = 0; i < n; i++){
		scanf("%s", name[i]);
		mp[name[i]] = mp.size();
	}

	for (int i = 0; i < n; i++){
		int k;
		scanf("%*s %d", &k);
		while (k--){
			scanf("%*s");
			while (1){
				string str;
				int last = 1;

				scanf("%s", buf);
				str = buf;
				if (str.back() == ','){
					str.pop_back();
					last = 0;
				}
				adj[i].push_back(mp[str]);

				if (last) break;
			}
		}
	}

	ans = INF;
	for (int i = 0; i < n; i++){
		bfs(i);
	}

	if (ans >= INF){
		printf("SHIP IT\n");
	}
	else{
		for (int it : ansv){
			printf("%s ", name[it]);
		}
		printf("\n");
	}
	return 0;
}
