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

char str[1000100];
int shortest[1000100];

int main()
{
	int n;
	ll ans;

	scanf("%d", &n);
	scanf("%s", str);

	get_fail(n, str);

	for (int i = 0; i < n; i++) {
		if (fail[i] == 0) {
			shortest[i] = i + 1;
		}
		else {
			shortest[i] = min(fail[i], shortest[fail[i] - 1]);
		}
	}

	ans = 0;
	for (int i = 0; i < n; i++) {
		ans += (i + 1) - shortest[i];
	}
	printf("%lld\n", ans);
	return 0;
}
