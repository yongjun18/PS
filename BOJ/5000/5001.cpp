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

char str[105];

int main()
{
	int x;
	int mcnt, wcnt;
	char keep;

	scanf("%d", &x);
	scanf("%s", str);

	keep = 0;
	mcnt = wcnt = 0;
	for (int i = 0; str[i]; i++) {
		if (keep == 'M' && abs(mcnt + 1 - wcnt) <= x) {
			mcnt++;
			keep = 0;
		}
		if (keep == 'W' && abs(wcnt + 1 - mcnt) <= x) {
			wcnt++;
			keep = 0;
		}
		if (str[i] == 'M'){
			if (abs(mcnt + 1 - wcnt) <= x) mcnt++;
			else if (keep == 0) keep = str[i];
			else break;
		}
		if (str[i] == 'W') {
			if (abs(wcnt + 1 - mcnt) <= x) wcnt++;
			else if (keep == 0) keep = str[i];
			else break;
		}
	}

	printf("%d\n", mcnt + wcnt);
	return 0;
}
