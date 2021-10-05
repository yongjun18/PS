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

int coins[55];

void play(int n) {
	vector< pair<int, int> > vec;
	int i1, i2;
	
	for (int i = 1; i <= n; i++) {
		vec.push_back({ coins[i], i });
	}
	sort(vec.rbegin(), vec.rend());
	
	i1 = vec[0].second;
	i2 = vec[1].second;
	coins[i1]--;
	coins[i2]--;
	printf("%d %d\n", i1, i2);
}

int main()
{
	int n;
	int sum, maxv;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &coins[i]);
	}

	sum = maxv = 0;
	for (int i = 1; i <= n; i++) {
		maxv = max(maxv, coins[i]);
		sum += coins[i];
	}

	if (sum % 2 == 0 && maxv <= sum - maxv) {
		printf("yes\n");
		for (int i = 0; i < sum / 2; i++) {
			play(n);
		}
	}
	else {
		printf("no\n");
	}

	return 0;
}
