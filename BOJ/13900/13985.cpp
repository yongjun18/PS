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
	int a, b, c;

	scanf("%d %*s %d %*s %d", &a, &b, &c);
	printf("%s\n", (a + b == c) ? "YES" : "NO");

	return 0;
}
