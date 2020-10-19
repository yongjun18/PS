#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[5010];

int main()
{
	int n;
	int minv;

	scanf("%d", &n);
	for(int i=0; i<2*n; i++){
		scanf("%d", &arr[i]);
	}
	sort(arr, arr+2*n);

	minv = INF;
	for(int i=0; i<n; i++){
		minv = min(minv, arr[i] + arr[2*n-1-i]);
	}
	printf("%d\n", minv);

	return 0;
}
