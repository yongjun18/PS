#include <bits/stdc++.h>
using namespace std;

char str[20];

int main() {
	int n;
	int ok = 1;
	
	scanf("%d", &n);
	scanf("%s", str);
	
	for(int i=2; str[i]; i++){
		if(str[i] != str[i%2]){
			ok = 0;
			break;
		}
	}
	printf("%s\n", ok ? "Yes" : "No");
	
	return 0;
}
