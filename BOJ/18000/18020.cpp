#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int check(ll n, ll m, ll a){
	if (n > m) swap(n, m);
	
	for(ll i=1; i*i <= a; i++){
		if(a % i == 0){
			if(i <= n && a / i <= m){
				return 1;
			}
		}
	}
	return 0;
}

int solve(ll n, ll m, ll a){
	if (a % n == 0 || a % m == 0) return 1;
	else if (check(n, m, a)) return 2;
	else return 3;
}

int main()
{
	ll n, m, a;
	int res1, res2;
	
	scanf("%lld %lld %lld", &n, &m, &a);
	
	res1 = solve(n, m, a);
	res2 = solve(n, m, n*m - a);
	printf("%d\n", min(res1, res2));
	
	return 0;
}
