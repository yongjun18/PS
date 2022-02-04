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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int arr[100100];

int main()
{
	int n, p;
	int pos;

	scanf("%d %d", &n, &p);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);

	pos = INF;
	for (int i = 0; i < n; i++) {
		int dist = (i + 1) *p;
		pos = min(pos, arr[i] - dist);
	}
	printf("%d\n", arr[0] - pos);
	return 0;
}
