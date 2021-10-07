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
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Tap {
	int t, a, b;
	bool operator < (const Tap& rhs) const {
		return t < rhs.t;
	}
};

vector<Tap> taps;
vector<int> used;

double get_temp() {
	ll v1, v2;
	v1 = v2 = 0;
	for (int i = 0; i < taps.size(); i++) {
		v2 += used[i];
		v1 += (ll)used[i] * taps[i].t;
	}
	return (double)v1 / v2;
}

int solve(int df, double& mint, double& maxt) {
	ll sum = 0;
	used = vector<int>(taps.size(), 0);

	for (int i = 0; i < taps.size(); i++) {
		used[i] = taps[i].a;
		sum += taps[i].a;
	}
	if (sum > df) return 0;
	for (int i = 0; i < taps.size(); i++) {
		int minv = min(df - sum, (ll)taps[i].b - used[i]);
		sum += minv;
		used[i] += minv;
	}
	if (sum < df) return 0;
	mint = get_temp();

	sum = 0;
	used = vector<int>(taps.size(), 0);
	for (int i = 0; i < taps.size(); i++) {
		used[i] = taps[i].a;
		sum += taps[i].a;
	}
	for (int i = (int)taps.size() - 1; i >= 0; i--) {
		int minv = min(df - sum, (ll)taps[i].b - used[i]);
		sum += minv;
		used[i] += minv;
	}
	maxt = get_temp();

	return 1;
}

int main()
{
	int k, r;
	
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		int t, a, b;
		scanf("%d %d %d", &t, &a, &b);
		taps.push_back({ t, a, b });
	}
	sort(taps.begin(), taps.end());

	scanf("%d", &r);
	
	for (int i = 0; i < r; i++) {
		int dt, df;
		double mint, maxt;
		int res;

		scanf("%d %d", &dt, &df);
		res = solve(df, mint, maxt);

		if (res == 1 && mint <= dt && dt <= maxt) {
			printf("yes\n");
		}
		else {
			printf("no\n");
		}
	}

	return 0;
}
