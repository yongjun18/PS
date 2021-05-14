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

int arr[100100];

int pxor[100100];
vector< pair<int, int> > xlist;

int first0[100100][35];

int main()
{
	int n;
	ll ans;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
		pxor[i] = (pxor[i - 1] ^ arr[i]);
		xlist.push_back({ pxor[i], i });
	}
	xlist.push_back({ 0, 0 });
	sort(xlist.begin(), xlist.end());

	for (int start = 1; start <= n; start++){
		for (int i = 0; i <= 30; i++){
			first0[start][i] = max(first0[start - 1][i], start);
			while (arr[first0[start][i]] & (1 << i)){
				first0[start][i]++;
			}
		}
	}

	ans = 0;
	for (int start = 1; start <= n; start++){
		vector<int> vec;
		int andv;

		for (int i = 0; i <= 30; i++){
			vec.push_back(first0[start][i]);
		}
		vec.push_back(start);
		vec.push_back(n + 1);
		sort(vec.begin(), vec.end());

		andv = (1 << 31) - 1;
		for (int i = 0; i + 1 < vec.size(); i++){
			int bg = vec[i];
			int ed = vec[i + 1];
			int xorv;
			int cnt;

			andv &= arr[bg];
			xorv = (andv ^ pxor[start - 1]);
			cnt = lower_bound(xlist.begin(), xlist.end(), make_pair(xorv, ed))
				- lower_bound(xlist.begin(), xlist.end(), make_pair(xorv, bg));
			ans += cnt;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
