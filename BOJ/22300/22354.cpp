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

char str[300100];
ll arr[300100];
vector<ll> vec;

int main()
{
	int n;
	int now, mx;
	ll maxv;
	ll sum;

	scanf("%d", &n);
	scanf("%s", str);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}

	now = 1;
	while (1){
		if (now >= n || str[now] != str[now - 1]) break;
		now++;
	}

	maxv = 0;
	while (1){
		maxv = max(maxv, arr[now]);
		now++;
		if (now >= n) break;
		if (str[now - 1] != str[now]){
			vec.push_back(maxv);
			maxv = 0;
		}
	}

	sort(vec.rbegin(), vec.rend());
	sum = 0;
	for (int i = 0; i < (vec.size() + 1) / 2; i++){
		sum += vec[i];
	}
	printf("%lld\n", sum);


	return 0;
}
