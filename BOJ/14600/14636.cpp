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
using namespace std;
typedef long long ll;
const ll INF = (ll)1e18 + 5;
const int MOD = 1e9 + 7;

vector< pair<ll, ll> > prod, prod2;
vector< pair<ll, ll> > cons, cons2;
ll ans;

void compute(int l, int r, int optl, int optr){
	if (l > r) return;

	int mid = (l + r) / 2;
	int opt = -1;
	ll maxv = -INF;

	for (int i = optl; i <= optr; i++){
		if (cons2[i].first < prod2[mid].first && cons2[i].second < prod2[mid].second){
			continue;
		}
		ll nowv = (cons2[i].first - prod2[mid].first) * (cons2[i].second - prod2[mid].second);
		if (maxv < nowv){
			maxv = nowv;
			opt = i;	
		}
	}
	ans = max(ans, maxv);

	if (opt == -1) return;
	compute(l, mid - 1, optl, opt);
	compute(mid + 1, r, opt, optr);
}

int main()
{
	int m, n;
	ll minv, maxv;

	scanf("%d %d", &m, &n);
	prod.resize(m);
	for (int i = 0; i < m; i++){
		scanf("%lld %lld", &prod[i].second, &prod[i].first);
	}
	cons.resize(n);
	for (int i = 0; i < n; i++){
		scanf("%lld %lld", &cons[i].second, &cons[i].first);
	}
	sort(prod.begin(), prod.end());
	sort(cons.begin(), cons.end());

	minv = INF;
	for (int i = 0; i < prod.size(); i++){
		if (minv > prod[i].second){
			minv = prod[i].second;
			prod2.push_back(prod[i]);
		}
	}
	maxv = 0;
	for (int i = (int)cons.size() - 1; i >= 0; i--){
		if (maxv < cons[i].second){
			maxv = cons[i].second;
			cons2.push_back(cons[i]);
		}
	}
	reverse(cons2.begin(), cons2.end());

	ans = 0;
	compute(0, (int)prod2.size() - 1, 0, (int)cons2.size() - 1);
	printf("%lld\n", ans);

	return 0;
}
