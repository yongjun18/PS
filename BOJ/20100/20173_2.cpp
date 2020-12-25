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
int now[1000100];

int main()
{
	int n;
	int ok;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}

	ok = 1;
	for (int i = 0; ok && i < n; i++){
		if (arr[i] > 2){
			ok = 0;
		}
	}

	for (int i = 0; ok && i < n - 1; i++){
		if (abs(arr[i] - now[i]) == 2){
			ok = 0;
		}
		if (abs(arr[i] - now[i]) == 1){
			now[i + 1]++;
		}
	}

	if (arr[n - 1] != now[n - 1]){
		ok = 0;
	}

	printf("%s\n", ok ? "YES" : "NO");
	return 0;
}
