#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char str[35];

void dfs(int now, int x, int y, int siz){
	if(siz == 1){
		printf("%d %d %d\n", now, y, x);
		return;
	}
	int num = str[now] - '0';

	if(num & 1) y += siz/2;
	if(num & 2) x += siz/2;
	dfs(now+1, x, y, siz/2);
}

int main()
{
	int len;

	scanf("%s", str);
	len = strlen(str);
	dfs(0, 0, 0, 1<<len);

	return 0;
}
