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

const int MX = 100200;

struct Node {
	int y, cnt, soaked;
	bool operator < (const Node& rhs) const {
		return y < rhs.y;
	}
};

vector< pair<int, int> > goblin;
vector<Node> arr[MX];

int distv(int x1, int y1, int x2, int y2) {
	return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
}

int main()
{
	int g, m;
	int ans;

	scanf("%d", &g);
	for (int i = 0; i < g; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		goblin.push_back({ x, y });
	}
	sort(goblin.begin(), goblin.end());

	for (auto it : goblin) {
		int nowx = it.first;
		int nowy = it.second;
		if (arr[nowx].size() > 0 && arr[nowx].back().y == nowy)
			arr[nowx].back().cnt++;
		else arr[nowx].push_back({ nowy, 1, 0 });
	}

	scanf("%d", &m);
	while (m--) {
		int x, y, r;
		scanf("%d %d %d", &x, &y, &r);

		for (int i = max(0, x - r); i <= x + r; i++) {
			Node tmp = { y - r , 0, 0 };
			auto it = lower_bound(arr[i].begin(), arr[i].end(), tmp);

			while (it != arr[i].end() && it->y <= y + r) {
				if (distv(i, it->y, x, y) <= r * r)
					it->soaked = 1;
				it++;
			}
		}
	}

	ans = 0;
	for (int i = 0; i < MX; i++) {
		for (auto it : arr[i]) {
			if (it.soaked == 0) {
				ans += it.cnt;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
