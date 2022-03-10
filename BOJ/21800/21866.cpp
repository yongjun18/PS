#include <bits/stdc++.h>
using namespace std;

int score[] = { 100, 100, 200, 200, 300, 300, 400, 400, 500 };
int arr[90];

int main() {
	int sum = 0;
	int hacker = 0;
	
	for(int i=0; i<9; i++){
		scanf("%d", &arr[i]);
		sum += arr[i];
		if(arr[i] > score[i]) hacker = 1;
	}
	
	if(hacker) printf("hacker\n");
	else if(sum >= 100) printf("draw\n");
	else printf("none\n");
	
	return 0;
}
