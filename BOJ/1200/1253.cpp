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

vector<int> arr;
vector<int> uniq;
vector<int> cnt;

int index(int x) {
	return lower_bound(uniq.begin(), uniq.end(), x) - uniq.begin();
}

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		arr.push_back(x);
	}
	for (int it : arr) {
		uniq.push_back(it);
	}
	sort(uniq.begin(), uniq.end());
	uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
	cnt.resize(uniq.size(), 0);

	for (int it : arr) {
		cnt[index(it)]++;
	}

	ans = 0;
	for (auto it1 : uniq) {
		int ok = 0;
		cnt[index(it1)]--;

		for (auto it2 : uniq) {
			if (cnt[index(it2)] == 0) continue;
			cnt[index(it2)]--;
			
			if (binary_search(uniq.begin(), uniq.end(), it1- it2)){
				if (cnt[index(it1 - it2)] > 0) {
					ok = 1;
				}
			}
			cnt[index(it2)]++;
		}
		cnt[index(it1)]++;
		if (ok) ans += cnt[index(it1)];
	}
	printf("%d\n", ans);
	return 0;
}
