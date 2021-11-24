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

const int MX = 1010;
int app[MX];
int learned[MX];

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		app[x] = 1;
	}
	for (int i = 0; i < n - 1; i++) {
		int x;
		scanf("%d", &x);
		learned[x] = 1;
	}

	ans = -1;
	for (int i = 0; i < MX; i++) {
		if (app[i] == 1 && learned[i] == 0) {
			ans = i;
			break;
		}
	}

	printf("%d\n", ans);
	return 0;
}
