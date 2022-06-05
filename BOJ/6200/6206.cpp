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
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 20010;

struct Hash {
	ll base;
	ll powv[MX];

	Hash(ll base) {
		this->base = base;
		powv[0] = 1;
		for (int i = 1; i < MX; i++) {
			powv[i] = (powv[i - 1] * base) % MOD;
		}
	}
	ll insert(ll hashv, int idx, ll val) {
		hashv += (powv[idx] * val) % MOD;
		hashv %= MOD;
		return hashv;
	}
	ll erase(ll hashv, int idx, ll val) {
		hashv -= (powv[idx] * val) % MOD;
		hashv = (hashv + MOD) % MOD;
		return hashv;
	}
	ll shift(ll hashv) {
		hashv *= base;
		hashv %= MOD;
		return hashv;
	}
};

Hash h1(13), h2(17);

int n, k;
int arr[MX];
map< pair<ll, ll>, int > appear;

int solve(int mid) {
	ll v1, v2;

	appear.clear();
	v1 = v2 = 0;
	for (int i = 0; i < n; i++) {
		if (i - mid >= 0) {
			v1 = h1.erase(v1, mid - 1, arr[i - mid]);
			v2 = h2.erase(v2, mid - 1, arr[i - mid]);
		}
		v1 = h1.shift(v1);
		v2 = h2.shift(v2);
		v1 = h1.insert(v1, 0, arr[i]);
		v2 = h2.insert(v2, 0, arr[i]);
		appear[{v1, v2}]++;
		
		if (appear[{v1, v2}] >= k) {
			return 1;
		}
	}
	return 0;
}

ll parametric_search(ll x, ll y) {
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%lld\n", parametric_search(1, n));
	return 0;
}
