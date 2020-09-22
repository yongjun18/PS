#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

ll compute(ll a, ll b, ll c){
	return a*a + b*b + c*c + 7 * min({a, b, c});
}

int main()
{
	int n;
	scanf("%d", &n);

	while(n--){
		ll a, b, c, d;
		ll maxv;

		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		maxv = 0;

		for(int i=0; i<=100; i++){
			for(int j=0; j<=100; j++){
				for(int k=0; k<=100; k++){
					if(i+j+k > d) continue;
					ll rest = d - (i+j+k);

					maxv = max(maxv, compute(a+i+rest, b+j, c+k));
					maxv = max(maxv, compute(a+i, b+j+rest, c+k));
					maxv = max(maxv, compute(a+i, b+j, c+k+rest));
				}
			}
		}
		printf("%lld\n", maxv);
	}
	return 0;
}
