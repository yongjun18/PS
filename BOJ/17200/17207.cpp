#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

char str[5][10] = { "Inseo", "Junsuk", "Jungwoo", "Jinwoo", "Youngki" };
int a[5][5];
int b[5][5];
int sum[5];

int main() {
	int ans, minv;
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			scanf("%d", &a[i][j]);
		}	
	}
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			scanf("%d", &b[i][j]);
		}	
	}
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			for(int k=0; k<5; k++){
				sum[i] += a[i][k] * b[k][j];
			}
		}
	}
	
	ans = minv = INF;
	for(int i=4; i>=0; i--){
		if(minv > sum[i]){
			minv = sum[i];
			ans = i;
		}
	}
	
	printf("%s\n", str[ans]);
	return 0;
}
