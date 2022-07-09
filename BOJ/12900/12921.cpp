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

int q[1005];
ll lo[1005];
ll hi[1005];
ll mid[1005];

int main()
{
	int n, m;
	ll x0, a, b;
	ll ans;

	scanf("%d %lld %lld %lld", &n, &x0, &a, &b);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &q[i]);
	}

	for (int i = 0; i < m; i++) {
		lo[i] = -1;
		hi[i] = MOD;
		mid[i] = (lo[i] + hi[i]) / 2;
	}
	for (int t = 0; t < 32; t++) {
		vector<ll> mids;
		vector<int> psum;
		ll nowx;

		for (int i = 0; i < m; i++) {
			mids.push_back(mid[i]);
		}
		sort(mids.begin(), mids.end());
		mids.erase(unique(mids.begin(), mids.end()), mids.end());
		psum = vector<int>(mids.size(), 0);

		nowx = x0;
		for (int i = 0; i < n; i++) {
			int pos = lower_bound(mids.begin(), mids.end(), nowx) - mids.begin();
			if (pos < mids.size()) {
				psum[pos]++;
			}
			nowx = (nowx * a + b) % MOD;
		}
		for (int i = 1; i < psum.size(); i++) {
			psum[i] += psum[i - 1];
		}

		for (int i = 0; i < m; i++) {
			int pos = lower_bound(mids.begin(), mids.end(), mid[i]) - mids.begin();
			if (psum[pos] >= q[i] + 1) hi[i] = mid[i];
			else lo[i] = mid[i];
			mid[i] = (lo[i] + hi[i]) / 2;
		}
	}

	ans = 0;
	for (int i = 0; i < m; i++) {
		ans += hi[i];
	}
	printf("%lld\n", ans);
	return 0;
}
