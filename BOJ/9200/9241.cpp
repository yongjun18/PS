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

char s[100100];
char t[100100];

int main()
{
	int slen, tlen;
	int lcnt, rcnt;
	int x, y;

	scanf("%s", s);
	scanf("%s", t);
	slen = strlen(s);
	tlen = strlen(t);

	lcnt = 0;
	rcnt = 0;
	
	x = y = 0;
	while (x < slen && y < tlen) {
		if (s[x] != t[y]) break;
		x++; y++;
		lcnt++;
	}

	x = slen - 1;
	y = tlen - 1;
	while (x >= 0 && y >= 0) {
		if (lcnt + rcnt + 1 > slen) break;
		if (lcnt + rcnt + 1 > tlen) break;
		if (s[x] != t[y]) break;
		x--; y--;
		rcnt++;
	}

	printf("%d\n", tlen - lcnt - rcnt);
	return 0;
}
