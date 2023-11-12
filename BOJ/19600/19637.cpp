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

struct Name {
	char str[15];
	int upperVal;
};

vector<Name> names;
char buf[15];

void print_name(int s) {
	int lo = -1;
	int hi = names.size();
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (s <= names[mid].upperVal) hi = mid;
		else lo = mid; 
	}
	printf("%s\n", names[hi].str);
}

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	names.resize(n);
	for (int i = 0; i < n; i++) {
		scanf(" %s %d", &names[i].str, &names[i].upperVal);
	}

	while (m--) {
		int s;
		scanf("%d", &s);
		print_name(s);
	}
	return 0;
}
