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

int seg[10][7] = {
	{1,1,1,0,1,1,1},
	{0,0,1,0,0,1,0},
	{1,0,1,1,1,0,1},
	{1,0,1,1,0,1,1},
	{0,1,1,1,0,1,0},
	{1,1,0,1,0,1,1},
	{1,1,0,1,1,1,1},
	{1,0,1,0,0,1,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1}
};
int n, k, p, x;

int compute(int from, int to) {
	int ret = 0;

	for (int i = 0; i < k; i++) {
		int f = from % 10;
		int t = to % 10;
		
		for (int j = 0; j < 7; j++) {
			if (seg[f][j] != seg[t][j]) {
				ret++;
			}
		}
		from /= 10;
		to /= 10;
	}
	return ret;
}

int main()
{
	int ans;

	scanf("%d %d %d %d", &n, &k, &p, &x);
	
	ans = 0;
	for (int i = 1; i <= n; i++) {
		if (x == i) continue;
		if (compute(x, i) <= p) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
