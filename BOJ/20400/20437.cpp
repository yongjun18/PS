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

char str[10100];
vector<int> appear[26];

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int k;
		int minv, maxv;
		scanf("%s", str);
		scanf("%d", &k);

		for (int i = 0; i < 26; i++) {
			appear[i].clear();
		}
		for (int i = 0; str[i]; i++) {
			appear[str[i] - 'a'].push_back(i);
		}

		maxv = -1;
		minv = INF;
		for (int i = 0; i < 26; i++) {
			for (int j = k - 1; j < appear[i].size(); j++) {
				int len = appear[i][j] - appear[i][j - k + 1] + 1;
				maxv = max(maxv, len);
				minv = min(minv, len);
			}
		}

		if (maxv == -1) printf("-1\n");
		else printf("%d %d\n", minv, maxv);
	}

	return 0;
}
