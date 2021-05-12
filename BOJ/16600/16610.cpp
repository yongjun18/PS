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

struct Group{
	int siz;
	ll val;
};

vector<Group> gs;
ll arr[100100];
int cycle[100100];

void build(){
	cycle[1] = 1;
	for (int i = 2; i < 100100; i++){
		cycle[i] = cycle[i / 2] + 1;
	}
}

void grouping(int n){
	int x = 1;
	int y = 1;
	while (x < n){
		while (y < n && arr[x] == arr[y]){
			y++;
		}
		gs.push_back({ y - x, arr[x] });
		x = y;
	}
	reverse(gs.begin(), gs.end());
}

int main()
{
	int n;
	ll ans = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}
	sort(arr + 1, arr + n);
	reverse(arr + 1, arr + n);
	grouping(n);
	build();

	while (1){
		int c = cycle[gs.back().siz];
		ll diff;
		if (gs.size() >= 2){
			diff = gs.back().val - (gs.rbegin() + 1)->val;
		}

		if (gs.size() == 1 || arr[0] < arr[1] + (c - 1) * diff){
			ll q = (arr[0] - arr[1] + 1) / (c - 1);
			ans += q * c;
			arr[1] += (c - 1) * q;

			if (arr[0] < arr[1]) ans--;
			ans += arr[0] - arr[1] + 1;
			break;
		}
		ans += c * diff;
		arr[1] += (c - 1) * diff;
		(gs.rbegin() + 1)->siz += gs.back().siz;
		gs.pop_back();
	}
	printf("%lld\n", ans - 1);
	return 0;
}
