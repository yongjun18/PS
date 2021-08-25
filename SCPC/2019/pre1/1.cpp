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

int dp[MX];
ll psum[MX];

int compute(int x){
	if (dp[x] != -1) return dp[x];
	if (x == 1) return dp[x] = 0;
	
	if (x % 2 == 1) return dp[x] = compute(x + 1) + 1;
	else return dp[x] = compute(x / 2) + 1;
}

int main()
{
	int t;

	memset(dp, -1, sizeof(dp));
	for (int i = 1; i < MX; i++){
		compute(i);
		psum[i] = psum[i - 1] + dp[i];
	}

	scanf("%d", &t);
	for (int test = 1; test <= t; test++){
		int n1, n2;
		scanf("%d %d", &n1, &n2);
		
		printf("Case #%d\n", test);
		printf("%lld\n", psum[n2] - psum[n1 - 1]);
	}

	return 0;
}
