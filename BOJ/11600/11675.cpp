#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int unscramble(int b){
	int a = (b & 1);

	for(int i=1; i<8; i++){
		if(b & (1<<i)){
			if((~a) & (1<<(i-1)))
				a += (1<<i);
		}
		else{
			if(a & (1<<(i-1)))
				a += (1<<i);
		}
	}
	return a;
}

int main()
{
	int n;
	scanf("%d", &n);

	while(n--){
		int b;
		scanf("%d", &b);
		printf("%d ", unscramble(b));
	}
	printf("\n");
	return 0;
}
