#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char str[105];
int a[105];
int k[105];
int b[105];

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);

	scanf("%s", str);
	for(int i=0; i<n; i++){
		a[m-n+i] = str[i] - 'a';
	}
	scanf("%s", str);
	for(int i=0; i<m; i++){
		b[i] = str[i] - 'a';
	}

	for(int i=m-n-1; i>=0; i--){
		k[i+n] = (b[i+n] - a[i+n] + 26) % 26;
		a[i] = k[i+n];
	}

	for(int i=0; i<m; i++)
		printf("%c", 'a'+a[i]);
	printf("\n");
	return 0;
}
