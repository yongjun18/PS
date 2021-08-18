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

vector< pair<ll, ll> > input;
vector< pair<ll, ll> > p;
vector< pair<ll, ll> > pol;
vector< pair<ll, ll> > k8;
vector<int> order;

ll dist(){
	ll ret = 0;
	for (int i = 0; i < 8; i++){
		ret += abs(p[i].first - pol[i].first);
		ret += abs(p[i].second - pol[i].second);
	}
	return ret;
}

ll compute(){
	ll ret;
	ll dx, dy;

	dx = p[0].first - k8[0].first;
	dy = p[0].second - k8[0].second;
	for (int i = 0; i < 8; i++){
		pol[i].first = k8[i].first + dx;
		pol[i].second = k8[i].second + dy;
	}
	ret = dist();

	for (int i = 1; i < 8; i++){
		ll ndx = p[i].first - k8[i].first;
		ll tmp;

		for (int j = 0; j < 8; j++){
			pol[j].first = k8[j].first + ndx;
		}
		tmp = dist();
		if (ret > tmp){
			ret = tmp;
			dx = ndx;
		}
	}
	for (int j = 0; j < 8; j++){
		pol[j].first = k8[j].first + dx;
	}

	for (int i = 1; i < 8; i++){
		ll ndy = p[i].second - k8[i].second;
		ll tmp;

		for (int j = 0; j < 8; j++){
			pol[j].second = k8[j].second + ndy;
		}
		tmp = dist();
		if (ret > tmp){
			ret = tmp;
			dy = ndy;
		}
	}
	for (int j = 0; j < 8; j++){
		pol[j].second = k8[j].second + dy;
	}
	return ret;
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		ll k;
		ll ans;

		input = p = pol = k8 = vector< pair<ll, ll> >(8);
		scanf("%lld", &k);
		for (int i = 0; i < 8; i++){
			scanf("%lld %lld", &input[i].first, &input[i].second);
		}
		k8[0] = { k, 0 };
		k8[1] = { 2 * k, 0 };
		k8[2] = { 3 * k, k };
		k8[3] = { 3 * k, 2 * k };
		k8[4] = { 2 * k, 3 * k };
		k8[5] = { k, 3 * k };
		k8[6] = { 0, 2 * k };
		k8[7] = { 0, k };

		order.clear();
		for (int i = 0; i < 8; i++){
			order.push_back(i);
		}

		ans = INF;
		while (1){
			for (int i = 0; i < 8; i++){
				p[i] = input[order[i]];
			}
			ans = min(ans, compute());

			if (next_permutation(order.begin(), order.end())) continue;
			break;
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
