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

const int MX = 1001000;

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

char t[MX];
char p[MX];
Hash h1(13), h2(17);

vector<int> ans;

int main()
{
	int n, m;
	ll p1, p2;
	ll t1, t2;
	
	fgets(t, MX, stdin);
	fgets(p, MX, stdin);
	n = strlen(t) - 1;
	m = strlen(p) - 1;

	p1 = p2 = 0;
	for (int i = 0; i < m; i++) {
		p1 = h1.shift(p1);
		p2 = h2.shift(p2);
		p1 = h1.insert(p1, 0, p[i]);
		p2 = h2.insert(p2, 0, p[i]);
	}

	t1 = t2 = 0;
	for (int i = 0; i < n; i++) {
		if (i - m >= 0) {
			t1 = h1.erase(t1, m - 1, t[i - m]);
			t2 = h2.erase(t2, m - 1, t[i - m]);
		}
		t1 = h1.shift(t1);
		t2 = h2.shift(t2);
		t1 = h1.insert(t1, 0, t[i]);
		t2 = h2.insert(t2, 0, t[i]);

		if (t1 == p1 && t2 == p2) {
			ans.push_back(i - m + 1);
		}
	}

	printf("%d\n", ans.size());
	for (int it : ans) {
		printf("%d ", it + 1);
	}
	printf("\n");
	return 0;
}
