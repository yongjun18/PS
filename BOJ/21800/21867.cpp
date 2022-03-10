#include <bits/stdc++.h>
using namespace std;

char str[200100];
string ans;

int main() {
	int n;
	
	scanf("%d", &n);
	scanf("%s", str);
	
	for(int i=0; i<n; i++){
		if(str[i] != 'J' && str[i] != 'A' && str[i] != 'V'){
			ans.push_back(str[i]);
		}
	}
	
	if(ans.size() == 0) printf("nojava\n");
	else printf("%s\n", ans.c_str());
	
	return 0;
}
