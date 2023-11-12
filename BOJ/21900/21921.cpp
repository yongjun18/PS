#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int arr[250100];

int main()
{
	int n, x;
	int nowsum, maxsum, cnt;

	scanf("%d %d", &n, &x);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	nowsum = 0;
	for (int i = 0; i < x; i++) {
		nowsum += arr[i];
	}
	maxsum = nowsum;
	cnt = 1;

	for (int i = x; i < n; i++) {
		nowsum += arr[i];
		nowsum -= arr[i - x];

		if (maxsum < nowsum) {
			maxsum = nowsum;
			cnt = 1;
		}
		else if (maxsum == nowsum) {
			cnt++;
		}
	}

	if (maxsum == 0) {
		printf("SAD\n");
	}
	else {
		printf("%d\n", maxsum);
		printf("%d\n", cnt);
	}

	return 0;
}
