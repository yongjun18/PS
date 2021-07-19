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
const ll INF = 1e15;
const int MOD = 1e9 + 7;

struct Node{
	vector<ll> vec;
	bool operator < (const Node& rhs) const{
		return vec[2] + vec[3] < rhs.vec[2] + rhs.vec[3];
	}
};

vector<Node> od, ev;


int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		int ecnt, ocnt;
		ll now, ans;

		scanf("%d %d", &n, &m);

		od.clear();
		ev.clear();

		for (int i = 0; i < n; i++){
			int l;
			vector<ll> vec, tmp;
			scanf("%d", &l);
			for (int j = 0; j < l; j++){
				ll x;
				scanf("%lld", &x);
				vec.push_back(x);
			}
			sort(vec.begin(), vec.end());
			for (int j = 0; j < 4; j++){
				tmp.push_back(vec[j]);
			}
			if (l % 2 == 1){
				od.push_back({ tmp });
			}
			else{
				ev.push_back({ tmp });
			}
		}
		sort(od.begin(), od.end());
		sort(ev.begin(), ev.end());
		ocnt = od.size();
		ecnt = ev.size();

		ans = INF;

		if (ocnt >= 2){
			now = 0;
			now += od[ocnt - 1].vec[0] * 2;
			now += od[ocnt - 1].vec[1];
			now += od[ocnt - 2].vec[0] * 2;
			now += od[ocnt - 2].vec[1];

			for (int i = 0; i < ocnt - 2; i++){
				now += od[i].vec[0] * 2;
				now += od[i].vec[1];
				now += od[i].vec[2];
				now += od[i].vec[3];
			}
			for (int i = 0; i < ecnt; i++){
				if (ocnt > 2){
					now += ev[i].vec[0];
					now += ev[i].vec[1];
					now += ev[i].vec[2];
					now += ev[i].vec[3];
				}
				else{
					now += ev[i].vec[0] * 2;
					now += ev[i].vec[1] * 2;
					now += ev[i].vec[2];
					now += ev[i].vec[3];
				}
			}
			ans = min(ans, now);
		}

		if (ocnt >= 1 && ecnt >= 1){
			now = 0;
			now += od[ocnt - 1].vec[0] * 2;
			now += od[ocnt - 1].vec[1];
			now += ev[ecnt - 1].vec[0];
			now += ev[ecnt - 1].vec[1];

			for (int i = 0; i < ocnt - 1; i++){
				now += od[i].vec[0] * 2;
				now += od[i].vec[1];
				now += od[i].vec[2];
				now += od[i].vec[3];
			}
			for (int i = 0; i < ecnt - 1; i++){
				now += ev[i].vec[0];
				now += ev[i].vec[1];
				now += ev[i].vec[2];
				now += ev[i].vec[3];
			}
			ans = min(ans, now);
		}

		if (ecnt >= 2){
			now = 0;
			now += ev[ecnt - 1].vec[0];
			now += ev[ecnt - 1].vec[1];
			now += ev[ecnt - 2].vec[0];
			now += ev[ecnt - 2].vec[1];

			for (int i = 0; i < ocnt; i++){
				now += od[i].vec[0] * 2;
				now += od[i].vec[1];
				now += od[i].vec[2];
				now += od[i].vec[3];
			}
			for (int i = 0; i < ecnt - 2; i++){
				now += ev[i].vec[0];
				now += ev[i].vec[1];
				now += ev[i].vec[2];
				now += ev[i].vec[3];
			}
			ans = min(ans, now);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
