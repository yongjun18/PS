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



int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	
	printf("%d\n", n / 2 + m / 2);
	for (int i = 2; i <= n; i += 2){
		printf("%d %d %d %d\n", i, 1, i, m);
	}
	for (int i = 2; i <= m; i += 2){
		printf("%d %d %d %d\n", 1, i, n, i);
	}
	return 0;
}
