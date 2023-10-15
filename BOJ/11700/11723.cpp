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

char str[10];
int exist[25];

int main()
{
	int m;

	scanf("%d", &m);
	while (m--) {
		scanf("%s", str);
		
		if (strcmp(str, "add") == 0) {
			int x;
			scanf("%d", &x);
			exist[x] = 1;
		}
		else if (strcmp(str, "remove") == 0) {
			int x;
			scanf("%d", &x);
			exist[x] = 0;
		}
		else if (strcmp(str, "check") == 0) {
			int x;
			scanf("%d", &x);
			printf("%d\n", exist[x]);
		}
		else if (strcmp(str, "toggle") == 0) {
			int x;
			scanf("%d", &x);
			exist[x] ^= 1;
		}
		else if (strcmp(str, "all") == 0) {
			for (int i = 0; i < 25; i++) {
				exist[i] = 1;
			}
		}
		else if (strcmp(str, "empty") == 0) {
			for (int i = 0; i < 25; i++) {
				exist[i] = 0;
			}
		}
	}

	return 0;
}
