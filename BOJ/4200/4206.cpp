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

vector<int> fail;
void get_fail(int m, const char* f) {
	fail = vector<int>(m, 0);
	int match = 0;
	for (int last = 1; last < m; last++) {
		while (match > 0 && f[last] != f[match])
			match = fail[match - 1];
		if (f[last] == f[match]) match++;
		fail[last] = match;
	}
}

char p[100100];
pair<ll, int> dp[3][100100];

int main()
{
	int n;
	int plen;

	for (int test = 1; scanf("%d", &n) > 0; test++) {
		scanf("%s", p);
		plen = strlen(p);
		get_fail(plen, p);

		for (int pv = 0; pv < plen; pv++) {
			int match = pv;
			ll appear = 0;
			while (match > 0 && p[match] != '0')
				match = fail[match - 1];
			if (p[match] == '0') match++;
			if (match == plen) {
				appear = 1;
				match = fail[match - 1];
			}
			dp[0][pv] = { appear,match };
		}
		for (int pv = 0; pv < plen; pv++) {
			int match = pv;
			ll appear = 0;
			while (match > 0 && p[match] != '1')
				match = fail[match - 1];
			if (p[match] == '1') match++;
			if (match == plen) {
				appear = 1;
				match = fail[match - 1];
			}
			dp[1][pv] = { appear, match };
		}
		for (int i = 2; i <= n; i++) {
			int i1 = (i - 1 + 3) % 3;
			int i2 = (i - 2 + 3) % 3;
			for (int pv = 0; pv < plen; pv++) {
				int mid = dp[i1][pv].second;
				ll appear = dp[i1][pv].first + dp[i2][mid].first;
				int state = dp[i2][mid].second;
				dp[i % 3][pv] = { appear, state };
			}
		}
		printf("Case %d: %lld\n", test, dp[n % 3][0].first);
	}
	return 0;
}
