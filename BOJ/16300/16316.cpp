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
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

char str[10];

int main()
{
	int n, val;
	int ok = 1;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%s", str);
		if (str[0] == 'm') continue;
		val = atoi(str);
		if (val != i){
			ok = 0;
			break;
		}
	}

	if (ok) printf("makes sense\n");
	else printf("something is fishy\n");

	return 0;
}
