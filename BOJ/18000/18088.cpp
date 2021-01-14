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

int arr[1000100];
int tmp[1000100];

int main()
{
	int n;
	int x, y;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
		tmp[i] = arr[i];
	}
	sort(tmp, tmp + n);

	x = 0;
	y = n - 1;
	while (x < n && arr[x] == tmp[x]) x++;
	while (y >= 0 && arr[y] == tmp[y]) y--;

	if (x >= n){
		printf("1 1\n");
	}
	else{
		int ok = 1;
		reverse(arr + x, arr + y + 1);
		for (int i = 0; i < n; i++){
			if (arr[i] != tmp[i]){
				ok = 0;
				break;
			}
		}
		if (ok == 0){
			printf("impossible\n");
		}
		else{
			printf("%d %d\n", x + 1, y + 1);
		}
	}

	return 0;
}
