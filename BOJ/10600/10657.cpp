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

vector<int> groups;

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x, speed;
		scanf("%d %d", &x, &speed);

		while (groups.size() > 0 && groups.back() > speed) {
			groups.pop_back();
		}
		groups.push_back(speed);
	}
	printf("%d\n", groups.size());
	return 0;
}
