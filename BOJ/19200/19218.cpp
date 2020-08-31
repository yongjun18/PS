#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Range{
	ll x, y, t;
	bool operator < (const Range& rhs) const{
		return x < rhs.x;
	}
};
vector<Range> rg;
set< pair<ll,ll> > set1, set2;

int main()
{
	int n, i;
	ll now, ans;
	scanf("%d", &n);

	rg.resize(n);
	for(int i=0; i<n; i++)
		scanf("%lld %lld %lld", &rg[i].x, &rg[i].y, &rg[i].t);
	sort(rg.begin(), rg.end());

	i = now = ans = 0;
	for(int i=0; i<n; i++)
		set2.insert({rg[i].x + rg[i].t, i});

	while(1){
		while(i < n && rg[i].x <= now){
			set1.insert({rg[i].t, i});
			set2.erase({rg[i].x + rg[i].t, i});
			i++;
		}
		while(set1.size() > 0){
			int idx = set1.begin()->second;
			if(now + rg[idx].t <= rg[idx].y) break;
			set1.erase(set1.begin());
		}

		vector< pair<ll,ll> > candi;
		if(set1.size() > 0){
			int idx = set1.begin()->second;
			candi.push_back({now + rg[idx].t, idx});
		}
		if(set2.size() > 0){
			candi.push_back(*set2.begin());
		}
		if(candi.size() == 0) break;
		sort(candi.begin(), candi.end());

		int idx = candi[0].second;
		now = max(now, rg[idx].x);

		ll to;
		if(i >= n) to = rg[idx].y;
		else to = min(rg[idx].y, rg[i].x);

		ll more = max((to - now) / rg[idx].t, 1LL);
		now += more * rg[idx].t;
		ans += more;
	}
	printf("%lld\n", ans);
	return 0;
}
