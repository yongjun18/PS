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
const int INF = 1e9 + 1;
const int MOD = 1e9 + 7;

vector<int> arr;

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		int ans;

		scanf("%d", &n);
		arr.clear();
		arr.push_back(INF);

		for (int i = 0; i < n; i++){
			int x;
			scanf("%d", &x);
			if (arr.back() == x) continue;
			arr.push_back(x);
		}
		arr.push_back(-INF);

		ans = 0;
		for (int i = 1; i + 1 < arr.size(); i++){
			if (arr[i - 1] < arr[i] && arr[i] > arr[i + 1]) 
				ans++;
			if (arr[i - 1] > arr[i] && arr[i] < arr[i + 1])
				ans++;
		}
		if (ans & 1) ans--;

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
