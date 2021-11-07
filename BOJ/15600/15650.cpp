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

vector<int> vec;

void dfs(int now, int n, int m) {
	if (now > n) return;

	vec.push_back(now);
	
	if (vec.size() == m) {
		for (int it : vec) printf("%d ", it);
		printf("\n");
	}
	else dfs(now + 1, n, m);

	vec.pop_back();
	dfs(now + 1, n, m);
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	dfs(1, n, m);

	return 0;
}
