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
	int l, r;

	scanf("%d %d", &l, &r);

	if (l + r == 0){
		printf("Not a moose\n");
	}
	else if (l == r){
		printf("Even %d\n", l + r);
	}
	else{
		printf("Odd %d\n", max(l, r) * 2);
	}

	return 0;
}
