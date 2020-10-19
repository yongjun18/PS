#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char arr1[10010];
char arr2[10010];
char tmp[10010];
char choice[3];

int dp[10010][3];

int main()
{
	int n;
	int x, y;
	int now;

	scanf("%d", &n);
	scanf("%s", arr1);
	scanf("%s", arr2);
	scanf("%d %d", &x, &y);

	choice[0] = arr1[x];
	choice[1] = arr1[y];
	now = 0;

	for(int i=0; i<n; i++){
		if(i == x || i == y) continue;
		tmp[now] = arr1[i];
		now++;
	}

	for(int i=0; i<n; i++){
		if(i==0 && arr2[i] == tmp[i])
			dp[i][0] = 1;
		if(i>0 && dp[i-1][0] && arr2[i] == tmp[i])
			dp[i][0] = 1;

		if(i==0 && arr2[i] == choice[0])
			dp[i][1] = 1;
		if(i>0 && dp[i-1][0] && arr2[i] == choice[0])
			dp[i][1] = 1;
		if(i>0 && dp[i-1][1] && arr2[i] == tmp[i-1])
			dp[i][1] = 1;

		if(i>0 && dp[i-1][1] && arr2[i] == choice[1])
			dp[i][2] = 1;
		if(i>1 && dp[i-1][2] && arr2[i] == tmp[i-2])
			dp[i][2] = 1;
	}

	if(dp[n-1][2]) printf("YES\n");
	else printf("NO\n");
	return 0;
}
