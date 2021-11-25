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

ll gcd(ll m, ll n) {
	while (n != 0) {
		ll t = m % n;
		m = n;
		n = t;
	}
	return m;
}

ll lcm(ll a, ll b) {
	return a * (b / gcd(a, b));
}

int main()
{
	int n;
	int ans = INF;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int y, c1, c2;
		scanf("%d %d %d", &y, &c1, &c2);
		ans = min(ans, y + (int)lcm(c1, c2));
	}

	printf("%d\n", ans);
	return 0;
}
