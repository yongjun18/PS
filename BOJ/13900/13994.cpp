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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

char str[1000100];
ll csum[1000100];
ll wsum[1000100];
double dp[1000100];
double dpsum[1000100];

int main()
{
	int len;

	scanf("%s", str);
	len = strlen(str);

	for (int i = len - 2; i >= 0; i--){
		if (str[i + 1] == 'C') csum[i] = csum[i + 1];
		else csum[i] = csum[i + 1] + len - 1 - i;
	}
	for (int i = len - 2; i >= 0; i--){
		if (str[i + 1] == 'W') wsum[i] = wsum[i + 1];
		else wsum[i] = wsum[i + 1] + len - 1 - i;
	}

	for (int i = len - 2; i >= 0; i--){
		if (str[i] == 'C'){
			dp[i] = (csum[i] + dpsum[i + 1]) / (len - i);
		}
		else{
			dp[i] = (wsum[i] + dpsum[i + 1]) / (len - i);
		}
		dpsum[i] = dpsum[i + 1] + dp[i];
	}
	printf("%.12lf\n", dp[0]);
	return 0;
}
