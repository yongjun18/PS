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

const int MX = 1000100;
int arr[100100];
vector<int> pos[MX];

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;
		ll ans;

		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++){
			scanf("%d", &arr[i]);
		}
		for (int i = 0; i < MX; i++){
			pos[i].clear();
		}

		for (int i = 1; i <= n; i++){
			for (int j = 1; j * j <= arr[i]; j++){
				if (arr[i] % j == 0){
					int div1 = j;
					int div2 = arr[i] / j;

					pos[div1].push_back(i);
					if (div1 != div2) pos[div2].push_back(i);
				}
			}
		}

		ans = 0;
		for (int i = 0; i < m; i++){
			int b, l, r;
			scanf("%d %d %d", &b, &l, &r);
			for (int j = 1; j * j <= b; j++){
				if (b % j == 0){
					int div1 = j;
					int div2 = b / j;
					vector<int>::iterator it;

					it = lower_bound(pos[div1].begin(), pos[div1].end(), l);
					if (it == pos[div1].end() || *it > r) ans++;

					if (div1 != div2){
						it = lower_bound(pos[div2].begin(), pos[div2].end(), l);
						if (it == pos[div2].end() || *it > r) ans++;
					}
				}
			}
		}
		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
