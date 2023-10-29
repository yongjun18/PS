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

int n, c;
int house[200100];

int solve(ll x) {
	int install = 1;
	int last = house[0];

	for (int i = 1; i < n; i++) {
		if (house[i] - last >= x) {
			last = house[i];
			install++;
		}
	}
	return install >= c;
}

ll parametric_search(ll x, ll y) {
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	scanf("%d %d", &n, &c);
	for (int i = 0; i < n; i++) {
		scanf("%d", &house[i]);
	}
	sort(house, house + n);

	printf("%lld\n", parametric_search(0, INF));
	return 0;
}
