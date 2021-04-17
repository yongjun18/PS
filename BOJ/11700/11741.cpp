#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <string>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int visit[10010][1010];
int tj[10010][1010];

int fi[10010];
int se[10010];

void print(int ans, int n){
	printf("%d\n", ans);
	for (int i = 0; i < n; i++){
		printf("%d ", tj[i][fi[i]]);
	}
	printf("\n");
}

int main()
{
	int n, k;
	int sum;

	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++){
		int x, a, b, c;
		scanf("%d %d %d %d", &x, &a, &b, &c);
		visit[i][x] = 1;
		tj[i][x] = 0;
		for (int j = 1;; j++){
			x = (x * a + b) % c;
			if (visit[i][x]) break;
			visit[i][x] = 1;
			tj[i][x] = j;
		}
	}

	for (int i = 0; i < n; i++){
		fi[i] = se[i] = -1;
		for (int j = 1000; j >= 0; j--){
			if (visit[i][j] == 0) continue;

			if (fi[i] == -1){
				fi[i] = j;
			}
			else if ((fi[i] - j) % k != 0 && se[i] == -1){
				se[i] = j;
			}
		}
	}
	
	sum = 0;
	for (int i = 0; i < n; i++){
		sum += fi[i];
	}

	if (sum % k != 0){
		print(sum, n);
	}
	else{
		int dmin = INF;
		int minidx = -1;
		for (int i = 0; i < n; i++){
			if (se[i] == -1) continue;
			if (dmin > fi[i] - se[i]){
				dmin = fi[i] - se[i];
				minidx = i;
			}
		}
		
		if (minidx == -1){
			printf("-1\n");
		}
		else{
			swap(fi[minidx], se[minidx]);
			print(sum - dmin, n);
		}
	}
	return 0;
}
