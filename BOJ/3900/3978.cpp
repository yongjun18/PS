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

const int MX = 10010;

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
char str[MX];
set< pair<ll, ll> > st;

string now;
int dfs(ll n1, ll n2, int k, int len) {
	if (now.size() == len) {
		if (st.find({ n1,n2 }) == st.end()) {
			printf("%s\n", now.c_str());
			return 1;
		}
		return 0;
	}

	for (char c = 'a'; c < 'a' + k; c++) {
		now.push_back(c);
		ll nxt1 = n1;
		ll nxt2 = n2;
		nxt1 = h1.shift(n1);
		nxt2 = h2.shift(n2);
		nxt1 = h1.insert(nxt1, 0, c);
		nxt2 = h2.insert(nxt2, 0, c);
		if (dfs(nxt1, nxt2, k, len)) {
			return 1;
		}
		now.pop_back();
	}
	return 0;
}

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int n, m, k;
		ll s1, s2;

		scanf("%d %d %d", &n, &m, &k);
		scanf("%s", str);

		s1 = s2 = 0;
		for (int i = 0; i < n; i++) {
			if (i - m >= 0) {
				s1 = h1.erase(s1, m - 1, str[i - m]);
				s2 = h2.erase(s2, m - 1, str[i - m]);
			}
			s1 = h1.shift(s1);
			s2 = h2.shift(s2);
			s1 = h1.insert(s1, 0, str[i]);
			s2 = h2.insert(s2, 0, str[i]);
			st.insert({ s1, s2 });
		}
		
		dfs(0, 0, k, m);
		st.clear();
		now.clear();
	}
	return 0;
}
