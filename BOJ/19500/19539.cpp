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
	int n;
	int ocnt, sum;

	scanf("%d", &n);

	sum = ocnt = 0;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		sum += x;
		if (x % 2 == 1) ocnt++;
	}

	if (sum % 3 == 0 && ocnt <= sum / 3){
		printf("YES\n");
	}
	else{
		printf("NO\n");
	}

	return 0;
}
