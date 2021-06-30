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
const ll INF = 1e12;
const int MOD = 1e9 + 7;

struct Line{
	ll x1, y1, x2, y2;
};
vector<Line> li;
vector<ll> usex, usey;

ll x, y;

int solve(ll len){
	for (Line it : li){
		if (it.x1 < x || it.y1 < y || it.x1 > x + len || it.y1 > y + len){
			if (it.x2 < x || it.y2 < y || it.x2 > x + len || it.y2 > y + len){
				return 0;
			}
		}
	}
	return 1;
}
ll bsearch(ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		ll ans, res;

		scanf("%d", &n);
		li = vector<Line>(n);
		usex.clear();
		usey.clear();
		for (int i = 0; i < n; i++){
			scanf("%lld %lld %lld %lld", &li[i].x1, &li[i].y1, &li[i].x2, &li[i].y2);
			usex.push_back(li[i].x1);
			usex.push_back(li[i].x2);
			usey.push_back(li[i].y1);
			usey.push_back(li[i].y2);
		}

		ans = INF;
		for (ll itx : usex){
			for (ll ity : usey){
				x = itx;
				y = ity;
				res = bsearch(0, INF);
				ans = min(ans, res);
			}
		}

		printf("Case #%d\n", test);
		
		printf("%lld", ans / 2);
		if (ans & 1) printf(".5\n");
		else printf("\n");
	}

	return 0;
}
