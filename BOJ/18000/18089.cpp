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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n;
ll c, r;
ll arr[500100];

int le[500100];
int ri[500100];
int erase[500100];
int tote;
vector< pair<ll, int> > vec;

ll case0(){
	int last = 0;
	int cnte = 0;

	for (int i = 0; i < n; i++){
		if (arr[i] == 0){
			cnte++;
			continue;
		}
		if (arr[i] > 0 && last > 0){
			cnte++;
		}
		if (arr[i] < 0 && last < 0){
			cnte++;
		}
		last = arr[i];
	}
	return cnte * r;
}

int check(int x){
	if (le[x] == -1) return 0;
	if (arr[le[x]] * arr[x] > 0 && (x - le[x]) % 2 == 1){
		return 1;
	}
	if (arr[le[x]] * arr[x] < 0 && (x - le[x]) % 2 == 0){
		return 1;
	}
	return 0;
}

ll case1(){
	int last = -1;
	for (int i = 0; i < n; i++){
		if (arr[i] == 0){
			le[i] = -1;
			continue;
		}
		le[i] = last;
		last = i;
	}

	last = -1;
	for (int i = n - 1; i >= 0; i--){
		if (arr[i] == 0){
			ri[i] = -1;
			continue;
		}
		ri[i] = last;
		last = i;
	}
	for (int i = 0; i < n; i++){
		if (arr[i] == 0) continue;
		erase[i] = check(i);
		tote += erase[i];
		vec.push_back({ abs(arr[i]), i });
	}
	sort(vec.begin(), vec.end());
	return c + r * tote;
}

int main()
{
	ll ans;

	scanf("%d %lld %lld", &n, &c, &r);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}

	ans = min(case0(), case1());
	for (auto it : vec){
		int i = it.second;
		tote -= erase[i];
		if (ri[i] != -1) tote -= erase[ri[i]];
		if (ri[i] != -1) le[ri[i]] = le[i];
		if (le[i] != -1) ri[le[i]] = ri[i];

		if (ri[i] != -1) {
			erase[ri[i]] = check(ri[i]);
			tote += erase[ri[i]];
		}
		ans = min(ans, (abs(arr[i]) + 1) * c + tote * r);
	}
	printf("%lld\n", ans);
	return 0;
}
