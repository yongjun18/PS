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

vector< pair<int, int> > input;
vector<int> arr1, arr2;
vector<int> len1, len2;

void LIS(vector<int>& arr, vector<int>& len) {
	vector<int> num, idx;
	len = vector<int>(arr.size(), 0);

	for (int i = 0; i < arr.size(); i++) {
		int pos;
		pos = lower_bound(num.begin(), num.end(), arr[i]) - num.begin();

		if (pos == num.size()) {
			num.push_back(arr[i]);
			idx.push_back(i);
		}
		else {
			num[pos] = arr[i];
			idx[pos] = i;
		}
		len[i] = pos + 1;
	}
}


int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		input.push_back({ x, i });
	}
	sort(input.begin(), input.end());
	
	for (int i = 0; i < n; i++){
		arr1.push_back(input[i].second);
	}
	arr2 = arr1;
	reverse(arr2.begin(), arr2.end());

	LIS(arr1, len1);
	LIS(arr2, len2);
	reverse(len2.begin(), len2.end());

	ans = 0;
	for (int i = 0; i < n; i++){
		ans = max(ans, len1[i] + len2[i] - 1);
	}
	printf("%d\n", ans);
	return 0;
}
