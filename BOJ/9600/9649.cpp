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

ll gcd(ll m, ll n){
	while (n != 0) {
		ll t = m % n;
		m = n;
		n = t;
	}
	return m;
}

int main()
{
	int x, y, z;

	while (scanf("%d %d %d", &x, &y, &z) > 0){
		int d = z-y;
		int n = x*y;
		int gcdv = gcd(d, n);
		d /= gcdv;
		n /= gcdv;

		printf("%d/%d\n", n, d);
	}

	return 0;
}
