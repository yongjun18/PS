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

int main()
{
	int n;
	int ok, psame;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}

	ok = 1;
	if (arr[0] == 0) psame = 1;
	else if (arr[0] == 1) psame = 0;
	else ok = 0;

	for (int i = 1; ok && i < n - 1; i++){
		if (arr[i] < 0 || 2 < arr[i]){
			ok = 0;
			break;
		}
		if (psame == 0){
			if (arr[i] % 2 == 0) psame = 0;
			else psame = 1;
		}
		else{
			if (arr[i] == 0) psame = 1;
			else if (arr[i] == 1) psame = 0;
			else ok = 0;
		}
	}

	if (psame == 1){
		if (arr[n - 1] != 0){
			ok = 0;
		}
	}
	if (psame == 0){
		if (arr[n - 1] != 1){
			ok = 0;
		}
	}
	printf("%s\n", ok ? "YES" : "NO");
	return 0;
}
