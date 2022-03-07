#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MX = 100100;
int check[MX];
ll psum[MX];

void init(){
	for(int i=3; i<MX; i+=3){
		check[i] = 1;
	}
	for(int i=7; i<MX; i+=7){
		check[i] = 1;
	}
	for(int i=1; i<MX; i++){
		psum[i] = psum[i-1];
		if(check[i]) psum[i] += i;
	}
}

int main() {
	int t;
	
	init();
	scanf("%d", &t);
	while(t--){
		int n;
		scanf("%d", &n);
		printf("%lld\n", psum[n]);	
	}
	
	return 0;
}
