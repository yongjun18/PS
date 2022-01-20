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



int main()
{
	ll x1, x2;
	int ok = 0;

	scanf("%lld%*c", &x1);

	for (int i = 0; i < 4; i++) {
		x1 *= 10;
		if (scanf("%1lld", &x2) > 0) x1 += x2;
	}
	
	for (int i = 1; i <= 100'000'000; i++) {
		ll goal, res;
		int fd, tmp;

		res = i * x1;
		if (res % 10000 != 0) continue;

		fd = i;
		tmp = 1;

		if (fd > 10000) {
			fd /= 10000;
			tmp *= 10000;
		}
		while (fd >= 10) {
			fd /= 10; tmp *= 10;
		}
		goal = (i % tmp) * 10 + fd;

		if (res / 10000 == goal) {
			printf("%d\n", i);
			ok = 1;
		}
	}

	if (ok == 0) printf("No solution\n");
	return 0;
}
