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

const int MX = 10200;

multiset<int> ms[MX];

int main()
{
	int g, m;
	int ans;

	scanf("%d", &g);

	for (int i = 0; i < g; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		ms[x].insert(y);
	}

	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int x, y, r;
		scanf("%d %d %d", &x, &y, &r);

		for (int i = max(0, x - r); i <= x + r; i++) {
			int tmp = (int)sqrt(r * r - (i - x) * (i - x));
			int from = y - tmp;
			int to = y + tmp;

			auto it = ms[i].lower_bound(from);
			while (it != ms[i].end() && *it <= to) 
				it = ms[i].erase(it);
		}
	}

	ans = 0;
	for (int i = 0; i < MX; i++) {
		ans += ms[i].size();
	}
	printf("%d\n", ans);
	return 0;
}
