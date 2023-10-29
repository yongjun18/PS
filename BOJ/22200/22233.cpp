#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

unordered_set<string> st;

char buf[120];

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		st.insert(buf);
	}

	for (int i = 0; i < m; i++) {
		char *pt;
		scanf("%s", buf);

		pt = strtok(buf, ",");
		while (pt != NULL) {
			st.erase(pt);
			pt = strtok(NULL, ",");
		}
		printf("%d\n", st.size());	
	}

	return 0;
}
