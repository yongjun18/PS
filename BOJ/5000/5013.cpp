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

char str[1010];

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	
	ans = 0;

	for (int i = 0; i < n; i++) {
		int ok = 1;
		scanf("%s", str);

		for (int j = 0; str[j + 1]; j++) {
			if (str[j] == 'C' && str[j + 1] == 'D') {
				ok = 0;
				break;
			}
		}
		ans += ok;
	}

	printf("%d\n", ans);
	return 0;
}
