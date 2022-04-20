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

vector<int> get_fail(int m, const char* f) {
	vector<int> fail(m, 0);
	int match = 0;
	for (int last = 1; last < m; last++) {
		while (match > 0 && f[last] != f[match])
			match = fail[match - 1];
		if (f[last] == f[match]) match++;
		fail[last] = match;
	}
	return fail;
}

vector<int> kmp(const char* a, const char* f) {
	int n = strlen(a), m = strlen(f);
	vector<int> ret;
	vector<int> fail = get_fail(m, f);

	int match = 0;
	for (int last = 0; last < n; last++) {
		while (match > 0 && a[last] != f[match])
			match = fail[match - 1];

		if (a[last] == f[match]) match++;
		if (match == m) {
			ret.push_back(last - match + 1);
			match = fail[match - 1];
		}
	}
	return ret;
}

char s[200100];
char s2[200100];
char k[200100];

int main()
{
	int now;

	scanf("%s %s", s, k);
	now = 0;
	for (int i = 0; s[i]; i++) {
		if ('0' <= s[i] && s[i] <= '9') continue;
		s2[now] = s[i];
		now++;
	}

	if (kmp(s2, k).size() > 0) printf("1\n");
	else printf("0\n");
	return 0;
}
