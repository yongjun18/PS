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

const int MX = 1000100;

vector<int> v1, v2;
int vis[MX];

int main()
{
	int f, s, g, u, d;

	scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);
	memset(vis, -1, sizeof(vis));

	v1.push_back(s);
	vis[s] = 0;

	for (int i = 1; v1.size() > 0; i++) {
		for (int it : v1) {
			if (it + u <= f && vis[it + u] == -1) {
				vis[it + u] = i;
				v2.push_back(it + u);
			}
			if (it - d >= 1 && vis[it - d] == -1) {
				vis[it - d] = i;
				v2.push_back(it - d);
			}
		}
		swap(v1, v2);
		v2.clear();
	}

	if (vis[g] == -1) printf("use the stairs\n");
	else printf("%d\n", vis[g]);
	return 0;
}
