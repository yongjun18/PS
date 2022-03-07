#include <bits/stdc++.h>
using namespace std;

int arr[1010];

int main() {
	int n, q;
	
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++){
		scanf("%d", &arr[i]);
	}
	
	while(q--){
		int res = 0;
		int x, y;
		scanf("%d %d", &x, &y);
		for(int i=x+1; i<=y; i++){
			res += abs(arr[i] - arr[i-1]);
		}
		printf("%d\n", res);
	}
	
	return 0;
}
