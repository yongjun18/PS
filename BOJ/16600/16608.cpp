#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int brk[500100];
int ans[500100];

int check(int n, int c, int nxt){
	while(nxt <= n && c > 0){
		while(brk[nxt] == 1) nxt++;

		if(c >= 2 && nxt < n){
			c -= 2;
			ans[nxt] = 1;
			nxt += 2;
		}
		else if(c >= 1 && nxt == n){
			c -= 1;
			ans[nxt] = 1;
			nxt += 2;
		}
		else nxt += 1;
	}
	if(c == 0) return 1;
	else return 0;
}

int main()
{
	int n, c, b;

	scanf("%d %d %d", &n, &c, &b);
	for(int i=1; i<=b; i++){
		int x;
		scanf("%d", &x);
		brk[x] = 1;
	}

	if(check(n, c, 2) == 0){
		ans[1] = 1;
		for(int i=2; i<=n; i++){
			ans[i] = 0;
		}
		check(n, c-1, 3);
	}

	for(int i=1; i<=n; i++){
		printf("%d", ans[i]);
	}
	printf("\n");
	return 0;
}
