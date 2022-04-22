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

char str[1000100];

int main()
{
	int l;
	
	scanf("%d", &l);
	scanf("%s", str);

	printf("%d\n", l - get_fail(l, str).back());
	return 0;
}
