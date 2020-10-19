#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
vector< pair<ll, ll> > rg;

int solve(ll x){
	ll cnt = 0;
	ll pv = -1e18;

	for(int i=0; i<rg.size(); i++){
		ll now = max(pv + x, rg[i].first);
		if(now > rg[i].second)
			continue;

		ll q = (rg[i].second - now) / x;
		cnt += q+1;
		pv = now + q*x;
	}
	return (cnt >= n);
}

ll parametric_search(ll x, ll y){
	ll lo = x-1;
	ll hi = y+1;

	while(lo+1 < hi){
		ll mid = (lo+hi)/2;
		if(solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	scanf("%d %d", &n, &m);
	rg.resize(m);
	for(int i=0; i<m; i++){
		scanf("%lld %lld", &rg[i].first, &rg[i].second);
	}
	sort(rg.begin(), rg.end());

	printf("%lld\n", parametric_search(0, 1e18));
	return 0;
}
