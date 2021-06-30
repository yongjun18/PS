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

ll gcd(ll m, ll n){
	while (n != 0) {
		ll t = m % n;
		m = n;
		n = t;
	}
	return m;
}

ll b[100100];

int divcnt(ll x){
	int ret = 0;
	for (ll i = 1; i * i <= x; i++){
		if (x % i == 0){
			if (i * i < x) ret += 2;
			else ret += 1;
		}
	}
	return ret;
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		int zcnt;
		ll gcdv;

		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			scanf("%lld", &b[i]);
		}
		
		zcnt = 0;
		gcdv = -1;
		for (int i = 1; i < n; i++){
			ll diff = b[i] - b[i - 1];
			if (diff == 0){
				zcnt++;
			}
			else{
				if (gcdv == -1) gcdv = diff;
				else gcdv = gcd(gcdv, diff);
			}
		}

		printf("Case #%d\n", test);
		if (zcnt > 0){
			if (zcnt == n - 1) printf("1\n");
			else printf("0\n");
		}
		else{
			printf("%d\n", divcnt(gcdv));
		}
	}

	return 0;
}
