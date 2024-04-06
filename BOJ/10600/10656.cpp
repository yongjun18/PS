#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Point { int x, y; };
char str[55][55];
vector<Point> ans;

int check(int x, int y) {
	if (str[x][y] == '#') {
		return 0;
	}
	if (y - 1 < 0 || str[x][y - 1] == '#') {
		if (str[x][y + 1] == '.' && str[x][y + 2] == '.') {
			return 1;
		}
	}
	if (x - 1 < 0 || str[x - 1][y] == '#') {
		if (str[x + 1][y] == '.' && str[x + 2][y] == '.') {
			return 1;
		}
	}
	return 0;
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf(" %s", str[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (check(i, j)) {
				ans.push_back({ i + 1, j + 1 });
			}
		}
	}
	printf("%d\n", ans.size());
	for (Point it : ans) {
		printf("%d %d\n", it.x, it.y);
	}
	return 0;
}
