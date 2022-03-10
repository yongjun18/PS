#include <bits/stdc++.h>
using namespace std;


int main() {
	int n;
	
	scanf("%d", &n);
	
	printf("%d\n", n + max(0, n - 2));
	for(int i=1; i<=n; i++){
		printf("%d 1\n", i);
	}
	for(int i=2; i<n; i++){
		printf("%d %d\n", i, n);
	}
	
	return 0;
}
