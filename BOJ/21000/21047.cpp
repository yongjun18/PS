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
#include <math.h>
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

char num[110][25];

int check(int n){
	for (int i = 1; i <= n; i++){
		for (int j = 0; num[i][j]; j++){
			char tmp = num[i][j];

			for (int k = 0; k < 10; k++){
				if (k == 0 && j == 0 && num[i][j + 1]) continue;
				num[i][j] = '0' + k;
				if (atoll(num[i - 1]) > atoll(num[i])){
					return 1;
				}
				if (atoll(num[i]) > atoll(num[i + 1])){
					return 1;
				}
			}
			num[i][j] = tmp;
		}
	}
	return 0;
}

int main()
{
	int n;
	int res;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%s", num[i]);
	}
	num[0][0] = '0';
	num[n + 1][0] = '1';
	for (int i = 1; i <= 16; i++){
		num[n + 1][i] = '0';
	}
	
	res = check(n);
	if (res){
		for (int i = 1; i <= n; i++)
			printf("%s ", num[i]);
		printf("\n");
	}
	else printf("impossible\n");

	return 0;
}
