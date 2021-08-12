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

int arr[55];

int main()
{
	int n;
	pair<int, int> minv;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}

	minv = make_pair(INF, INF);
	for (int i = 0; i + 2 < n; i++){
		minv = min(minv, make_pair(max(arr[i], arr[i + 2]), i + 1));
	}
	printf("%d %d\n", minv.second, minv.first);
	return 0;
}
