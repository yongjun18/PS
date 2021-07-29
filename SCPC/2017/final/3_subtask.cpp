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
const ll INF = 1e11;
const int MOD = 1e9 + 7;

vector< pair<ll, ll> > pt1, pt2;

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		ll ans = INF;

		scanf("%d", &n);
		pt1.resize(n);
		pt2.resize(n);
		for (int i = 0; i < n; i++){
			scanf("%lld %lld %lld %lld", 
				&pt1[i].first, &pt1[i].second, &pt2[i].first, &pt2[i].second);
		}
		
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				ll dist = abs(pt1[i].first - pt2[j].first) 
					+ abs(pt1[i].second - pt2[j].second);
				ll nowv = max(dist + i + 1, j + 1LL);
				ans = min(ans, nowv);
			}
		}

		printf("Case #%d\n", test);
		if (ans > n) printf("-1\n");
		else printf("%lld\n", ans);
	}

	return 0;
}
