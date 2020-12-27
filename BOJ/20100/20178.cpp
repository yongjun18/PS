#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
int arr[505][505];
int inv[505][505];

void pluss(int to, int from){
	for (int j = 0; j < n; j++){
		arr[to][j] += arr[from][j];
		inv[to][j] += inv[from][j];

		arr[to][j] %= 2;
		inv[to][j] %= 2;
	}
}

int get_inv(){
	for (int i = 0; i < n; i++){
		inv[i][i] = 1;
	}

	for (int i = 0; i < n; i++){
		for (int j = i + 1; arr[i][i] == 0 && j < n; j++){
			if (arr[j][i] == 1){
				pluss(i, j);
			}
		}
		if (arr[i][i] == 0){
			return 0;
		}
		for (int j = i + 1; j < n; j++){
			if (arr[j][i] == 1){
				pluss(j, i);
			}
		}
	}

	for (int i = n - 1; i >= 0; i--){
		for (int j = i - 1; j >= 0; j--){
			if (arr[j][i] == 1){
				pluss(j, i);
			}
		}
	}
	return 1;
}

int main()
{
	int res;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			scanf("%d", &arr[j][i]);
		}
	}

	res = get_inv();
	if (res == 1){
		for (int j = 0; j < n; j++){
			for (int i = 0; i < n; i++){
				if (inv[i][j] == 1){
					printf("%d ", i + 1);
				}
			}
			printf("\n");
		}
	}
	else{
		printf("-1\n");
	}

	return 0;
}
