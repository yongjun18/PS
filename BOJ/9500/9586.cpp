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
int first0[100100][35];
int pxor[100100];

vector< pair<int, int> > vec;

int main()
{
	int n;
	ll ans;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
	}

	for (int b = 0; b <= 30; b++){
		for (int i = 1; i <= n; i++){
			first0[i][b] = max(first0[i - 1][b], i + 1);
			while ((1 << b) & arr[first0[i][b]]){
				first0[i][b]++;
			}
		}
	}

	for (int i = 1; i <= n; i++){
		pxor[i] = (pxor[i - 1] ^ arr[i]);
		vec.push_back({ pxor[i], i });
	}
	sort(vec.begin(), vec.end());

	ans = 0;
	for (int i = n; i >= 1; i--){
		vector<int> chg;
		int andv;

		chg.push_back(i);
		for (int b = 0; b <= 30; b++){
			chg.push_back(first0[i][b]);
		}
		sort(chg.begin() + 1, chg.end());
		chg.push_back(n + 1);

		andv = arr[i];
		for (int j = 0; j + 1 < chg.size(); j++){
			int x = chg[j];
			int y = chg[j + 1];
			int findv = andv ^ pxor[i - 1];
			int cnt = lower_bound(vec.begin(), vec.end(), make_pair(findv, y))
				- lower_bound(vec.begin(), vec.end(), make_pair(findv, x));
			ans += cnt;
			andv &= arr[y];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
