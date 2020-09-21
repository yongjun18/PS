#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int main()
{
	int n;
	scanf("%d", &n);

	if(n <= 3)
		printf("1\n");
	else printf("%d\n", n-2);
	return 0;
}
