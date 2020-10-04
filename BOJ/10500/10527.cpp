#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

multiset<string> ms;
char str[20];

int main()
{
	int n;
	int ans;
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		scanf("%s", str);
		ms.insert(str);
	}

	ans = 0;
	for(int i=0; i<n; i++){
		scanf("%s", str);
		auto it = ms.find(str);
		if(it != ms.end()){
			ans++;
			ms.erase(it);
		}
	}
	printf("%d\n", ans);
	return 0;
}
