#include <bits/stdc++.h>
using namespace std;

char a[10];
char b[10];
vector<int> v1, v2;

int main() {
	scanf("%s %s", a, b);
	
	for(int i=0; i<8; i++){
		v1.push_back(a[i] - '0');
		v1.push_back(b[i] - '0');
	}
	
	while(v1.size() > 2){
		for(int i=1; i<v1.size(); i++){
			v2.push_back((v1[i-1] + v1[i]) % 10);
		}
		swap(v1, v2);
		v2.clear();
	}
	printf("%d%d\n", v1[0], v1[1]);
	return 0;
}
