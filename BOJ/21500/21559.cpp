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

const int MX = 100100;

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

char a[MX];
char b[MX];
set< pair<ll, ll> > asub, ans;

int main()
{
	int n, k;
	ll a1, a2, b1, b2;

	scanf("%d %d", &n, &k);
	scanf("%s %s", a, b);

	a1 = a2 = 0;
	for (int i = 0; i < k; i++) {
		a1 = h1.shift(a1);
		a2 = h2.shift(a2);
		a1 = h1.insert(a1, 0, a[i]);
		a2 = h2.insert(a2, 0, a[i]);
	}
	asub.insert({ a1, a2 });

	for (int i = k; i < n; i++) {
		a1 = h1.erase(a1, k - 1, a[i - k]);
		a2 = h2.erase(a2, k - 1, a[i - k]);
		a1 = h1.shift(a1);
		a2 = h2.shift(a2);
		a1 = h1.insert(a1, 0, a[i]);
		a2 = h2.insert(a2, 0, a[i]);
		
		asub.insert({ a1, a2 });
	}

	b1 = b2 = 0;
	for (int i = 0; i < k; i++) {
		b1 = h1.shift(b1);
		b2 = h2.shift(b2);
		b1 = h1.insert(b1, 0, b[i]);
		b2 = h2.insert(b2, 0, b[i]);
	}
	if (asub.find({ b1, b2 }) != asub.end()) {
		ans.insert({ b1, b2 });
	}

	for (int i = k; i < n; i++) {
		b1 = h1.erase(b1, k - 1, b[i - k]);
		b2 = h2.erase(b2, k - 1, b[i - k]);
		b1 = h1.shift(b1);
		b2 = h2.shift(b2);
		b1 = h1.insert(b1, 0, b[i]);
		b2 = h2.insert(b2, 0, b[i]);

		if (asub.find({ b1, b2 }) != asub.end()) {
			ans.insert({ b1, b2 });
		}
	}
	printf("%d\n", ans.size());
	return 0;
}
