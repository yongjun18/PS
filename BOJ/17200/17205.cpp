#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll len[11];
char str[11];

void init(){
	len[0] = 0;
	for(int i=1; i<=10; i++){
		len[i] = 26 * (len[i-1] + 1);
	}
}

int main() {
	ll ans = 0;
	
	scanf("%d", &n);
	scanf("%s", str);
	init();
	
	for(int i=0; str[i]; i++){
		ans += 1 + (str[i] - 'a') * (len[n-i-1] + 1);
	}
	printf("%lld\n", ans);
	return 0;
}
