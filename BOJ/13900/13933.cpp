#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n;
int arr1[1000100];
int arr2[1000100];

int solve(ll x){
	vector<int> v1, v2;

	for(int i=0; i<n; i++){
		if(arr1[i] > x)
			v1.push_back(arr1[i]);
		if(arr2[i] > x)
			v2.push_back(arr2[i]);
	}

	if(v1.size() % 2 == 1)
		return 0;
	if(v2.size() % 2 == 1)
		return 0;

	for(int i=0; i<v1.size(); i++){
		if(i % 2 == 1 && v1[i-1] != v1[i])
			return 0;
	}
	for(int i=0; i<v2.size(); i++){
		if(i % 2 == 1 && v2[i-1] != v2[i])
			return 0;
	}
	return 1;
}

ll parametric_search(ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(mid)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main()
{
	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &arr1[i]);
	for(int i=0; i<n; i++)
		scanf("%d", &arr2[i]);

	printf("%lld\n", parametric_search(0, 1e9));
	return 0;
}
