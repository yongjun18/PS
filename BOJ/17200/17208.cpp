#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dp[105][305][305];
int a[105];
int b[105];

int main() {
	int n, m, k;
	int maxv;
	
	scanf("%d %d %d", &n, &m, &k);
	for(int i=1; i<=n; i++){
		scanf("%d %d", &a[i], &b[i]);
	}
	
	for(int i=0; i<n; i++){
		for(int j=0; j<=m; j++){
			for(int p=0; p<=k; p++){
				int nj = j + a[i+1];
				int np = p + b[i+1];
				if(nj <= m && np <= k){
					dp[i+1][nj][np] = max(dp[i+1][nj][np], dp[i][j][p] + 1);	
				}
				dp[i+1][j][p] = max(dp[i+1][j][p], dp[i][j][p]);
			}
		}
	}
	
	maxv = 0;
	for(int i=0; i<=m; i++){
		for(int j=0; j<=k; j++){
			maxv = max(maxv, dp[n][i][j]);
		}
	}
	printf("%d\n", maxv);
	
	return 0;
}
