#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char a[65];
char b[65];

int main()
{
	int n;
	ll apos, bpos;
	int cnt1;

	scanf("%d", &n);
	scanf("%s %s", a, b);

	apos = 0;
	cnt1 = 0;
	for(int i=0; i<n; i++){
		if(cnt1 % 2 == 0 && a[i] == '1')
			apos += (1LL << (n-i-1));
		if(cnt1 % 2 == 1 && a[i] == '0')
			apos += (1LL << (n-i-1));
		if(a[i] == '1') cnt1++;
	}

	bpos = 0;
	cnt1 = 0;
	for(int i=0; i<n; i++){
		if(cnt1 % 2 == 0 && b[i] == '1')
			bpos += (1LL << (n-i-1));
		if(cnt1 % 2 == 1 && b[i] == '0')
			bpos += (1LL << (n-i-1));
		if(b[i] == '1') cnt1++;
	}

	printf("%lld\n", bpos - apos - 1);
	return 0;
}
