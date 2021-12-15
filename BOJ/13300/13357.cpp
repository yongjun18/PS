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

ll arr[370];

int main()
{
	int n;
	ll money, stock;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lld", &arr[i]);
	}

	money = 100;
	stock = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] < arr[i + 1]) {
			ll amount = min(100'000 - stock, money / arr[i]);
			money -= amount * arr[i];
			stock += amount;
		}
		else {
			money += stock * arr[i];
			stock = 0;
		}
	}
	
	printf("%lld\n", money);

	return 0;
}
