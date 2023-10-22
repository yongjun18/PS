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

vector<string> names;
char buf[25];

int main()
{
	int n;
	char t;

	scanf("%d %c", &n, &t);
	for (int i = 0; i < n; i++) {
		scanf("%s", buf);
		names.push_back(buf);
	}
	
	sort(names.begin(), names.end());
	names.erase(unique(names.begin(), names.end()), names.end());

	if (t == 'Y') {
		printf("%d\n", names.size());
	}
	else if (t == 'F') {
		printf("%d\n", names.size() / 2);
	}
	else {
		printf("%d\n", names.size() / 3);
	}
	return 0;
}
