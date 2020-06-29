#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e18+7;
const int MOD = 1e9+7;

int w;
ll n;
ll hei[100100];
ll rhei[100100];

ll le[100100];
ll ri[100100];
int arr[100100];

void build(ll x, ll h[], ll r[], int to[]){
    r[0] = 0;
    to[0] = 0;
    for(int i=1; i<=w+1; i++){
        if(h[i] >= x){
            r[i] = 0;
            to[i] = i;
            continue;
        }
        r[i] = r[i-1];
        if(i <= to[i-1]) r[i] -= x-1-h[i];
        if(to[i-1]-i > 0) r[i] += to[i-1]-i;
        to[i] = max(to[i-1], i);

        while(to[i] < w+1 && h[to[i]+1] < x-(to[i]+1-i)){
            r[i] += x-(to[i]+1-i) - h[to[i]+1];
            to[i]++;
        }
        if(to[i] == w+1) r[i] = INF;
    }
}
int solve(ll x){
    build(x, hei, ri, arr);
    build(x, rhei, le, arr);
    reverse(le, le+w+2);

    for(int i=1; i<=w; i++){
        ll need = le[i] + max(0LL, x-hei[i]) + ri[i];
        if(need <= n) return 1;
    }
    return 0;
}
ll bin_search(ll x, ll y) {
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		if (solve(mid)) lo = mid;
		else hi = mid;
	}
	return lo;
}

int main()
{
    scanf("%d %lld", &w, &n);
    for(int i=1; i<=w; i++){
        scanf("%lld", &hei[i]);
        rhei[i] = hei[i];
    }
    hei[0] = hei[w+1] = rhei[0] = rhei[w+1] = -INF;
    reverse(rhei, rhei+w+2);

    printf("%lld\n", bin_search(1, (ll)1e18));
    return 0;
}
