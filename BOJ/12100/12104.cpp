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

char a[MX];
char b[MX * 2];

Hash h1(13), h2(17);

int main()
{
	int n, m;
	ll a1, a2, b1, b2;
	int ans;

	scanf("%s %s", a, b);
	
	n = strlen(a);
	m = n + n - 1;
	for (int i = n; i < m; i++) {
		b[i] = b[i - n];
	}

	a1 = a2 = 0;
	for (int i = 0; i < n; i++) {
		a1 = h1.shift(a1);
		a2 = h2.shift(a2);
		a1 = h1.insert(a1, 0, a[i]);
		a2 = h2.insert(a2, 0, a[i]);
	}

	ans = 0;
	b1 = b2 = 0;
	for (int i = 0; i < m; i++) {
		if (i - n >= 0) {
			b1 = h1.erase(b1, n - 1, b[i - n]);
			b2 = h2.erase(b2, n - 1, b[i - n]);
		}
		b1 = h1.shift(b1);
		b2 = h2.shift(b2);
		b1 = h1.insert(b1, 0, b[i]);
		b2 = h2.insert(b2, 0, b[i]);

		if (a1 == b1 && a2 == b2) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
