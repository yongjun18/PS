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

ll xsum[5010];
ll ysum[5010];
int cnt[5010];
set<int> removed[5010];

int main()
{
	int n, w, h, m;
	int ok;

	scanf("%d %d %d %d", &n, &w, &h, &m);
	w = 2;

	for (int i = 1; i <= h; i++){
		xsum[i] = (ll)n * n;
		ysum[i] = (ll)n * n;
		cnt[i] = n;
	}

	ok = 0;
	for (int i = 1; i <= m; i++){
		int lev, x;
		ll uxsum, uysum, cntsum;
		double tmp;
		int l, r;
		scanf("%d %d", &lev, &x);

		cnt[lev]--;
		if (lev % 2 == 1){
			xsum[lev] -= 2 * x - 1;
			ysum[lev] -= n;
		}
		else{
			xsum[lev] -= n;
			ysum[lev] -= 2 * x - 1;
		}
		removed[lev].insert(x);

		uxsum = uysum = cntsum = 0;

		for (int j = h; j >= 1; j--){
			if (cntsum > 0){
				l = 1;
				r = n;
				for (auto it = removed[j].begin(); it != removed[j].end(); it++){
					if (l == *it) l++;
					else break;
				}
				for (auto it = removed[j].rbegin(); it != removed[j].rend(); it++){
					if (r == *it) r--;
					else break;
				}

				if (j % 2 == 1) tmp = (double)uxsum / cntsum;
				else tmp = (double)uysum / cntsum;

				if (l > n || !(2 * l - 2 < tmp && tmp < 2 * r)){
					ok = 1;
					printf("yes\n");
					printf("%d\n", i);
					break;
				}
			}
			uxsum += xsum[j];
			uysum += ysum[j];
			cntsum += cnt[j];
		}
		if (ok) break;
	}
	if (ok == 0){
		printf("no\n");
	}
	return 0;
}
