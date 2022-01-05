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

char str[305];

int main()
{
	int ans;

	scanf("%s", str);

	ans = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] != "PER"[i % 3]) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
