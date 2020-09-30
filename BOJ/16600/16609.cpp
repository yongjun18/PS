#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int arr[200100];

int main()
{
	int n;
	int poss;
	double minv;

	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		scanf("%d", &arr[i]);
	}
	sort(arr+1, arr+n+1);

	minv = 1.0;
	poss = 1;
	for(int i=1; i<=n; i++){
		if(arr[i] > i){
			poss = 0;
			break;
		}
		else{
			minv = min(minv, (double)arr[i] / i);
		}
	}

	if(poss)
		printf("%.9lf\n", minv);
	else printf("impossible\n");
	return 0;
}
