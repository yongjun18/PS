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

const int BUY = 1;
const int SELL = 2;

ll arr[370];
int state[370];

int main()
{
	int n;
	ll money, stock;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
	}

	for (int i = 0; i < n; i++) {
		if ((i == 0 || arr[i - 1] >= arr[i]) && 
			(i + 1 < n && arr[i] < arr[i + 1]))
			state[i] = BUY;

		if ((i == n - 1 || arr[i] >= arr[i + 1]) && 
			(i > 0 && arr[i - 1] < arr[i]))
			state[i] = SELL;
	}

	money = 100;
	stock = 0;

	for (int i = 0; i < n; i++) {
		if (state[i] == BUY) {
			ll amount = min((ll)100'000, money / arr[i]);
			stock += amount;
			money -= amount * arr[i];
		}
		if (state[i] == SELL) {
			money += stock * arr[i];
			stock = 0;
		}
	}
	printf("%lld\n", money);

	return 0;
}
