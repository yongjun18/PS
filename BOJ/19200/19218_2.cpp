#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <set>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const ll INF = (ll)1e18 + 5;
const int MOD = 1e9 + 7;

ll a[200100];
ll b[200100];
ll t[200100];

struct Event{
	ll t;
	int idx, type;
	bool operator < (const Event& rhs) const{
		if (t != rhs.t) return t < rhs.t;
		if (idx != rhs.idx) return idx < rhs.idx;
		return type < rhs.type;
	}
};

vector<Event> evt;

struct Node{
	ll ti;
	int idx;
	bool operator < (const Node& rhs) const{
		if (ti != rhs.ti) return ti < rhs.ti;
		return idx < rhs.idx;
	}
};

set<Node> st;

int main()
{
	int n;
	ll firstm, ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%lld %lld %lld", &a[i], &b[i], &t[i]);
	}

	for (int i = 0; i < n; i++){
		evt.push_back({ a[i], i, 1 });
		evt.push_back({ b[i], i, -1 });
	}
	sort(evt.begin(), evt.end());

	ans = 0;
	firstm = INF;
	for (int i = 0; i < evt.size(); i++){
		if (firstm <= evt[i].t){
			ans++;
			ll dt = evt[i].t - firstm;
			ll q = dt / st.begin()->ti;
			ll last = firstm + q * st.begin()->ti;
			ans += q;
			
			while (st.size()){
				int idx = st.begin()->idx;
				if (last + t[idx] <= b[idx]) break;
				st.erase(st.begin());
			}
			if (st.size()){
				firstm = last + st.begin()->ti;
			}
			else{
				firstm = INF;
			}
		}

		if (evt[i].type == 1){
			int idx = evt[i].idx;
			st.insert({ t[idx], idx });
			firstm = min(firstm, a[idx] + t[idx]);
		}
	}

	printf("%lld\n", ans);
	return 0;
}
