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

int arr[10][20];
int check[10][20];

int main()
{
	int n, k;
	int maxv, midx;
	int sum;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < 20; j++){
			arr[i][j] = 50;
		}
	}
	maxv = -1;
	midx = -1;
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		if (maxv <= x){
			maxv = x;
			midx = i;
		}
		for (int j = 0; j < x; j++){
			scanf("%d", &arr[i][j]);
		}
	}
	check[midx][maxv - 1] = 1;

	sum = 0;
	for (int j = 0; j < 20; j++){
		for (int i = 0; i < n; i++){
			if (k > 0 && sum <= arr[i][j]){
				sum += arr[i][j];
				k--;
			}
			if (check[i][j] == 1) break;
		}
	}
	sum += k * 50;
	printf("%d\n", sum);
	return 0;
}
