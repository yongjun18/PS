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

int m, n, p;
vector<int> usey;
vector< pair<int, int> > can[1010];
int arr[15][1010];
vector< pair<int, int> > po;
int powv;

int dp[60100][1010];

void compress(){
	sort(usey.begin(), usey.end());
	usey.erase(unique(usey.begin(), usey.end()), usey.end());

	for (auto &it : po){
		it.second = lower_bound(usey.begin(), usey.end(), it.second) - usey.begin();
	}
	for (auto it : po){
		arr[it.first][it.second] = 1;
	}
}

void build_can(){
	for (int i = 0; i <= m; i++){
		for (int j = 0; j < usey.size(); j++){
			int cnt = 0;
			cnt += arr[i][j];
			cnt += arr[i + 1][j];
			cnt += arr[i + 2][j];

			if (j > 0 && usey[j] - usey[j - 1] <= 2){
				cnt += arr[i][j - 1];
				cnt += arr[i + 1][j - 1];
				cnt += arr[i + 2][j - 1];
			}
			if (j > 1 && usey[j] - usey[j - 2] <= 2){
				cnt += arr[i][j - 2];
				cnt += arr[i + 1][j - 2];
				cnt += arr[i + 2][j - 2];
			}

			if (cnt >= 2){
				can[j].push_back({ i, j });
			}
		}
	}
}

void transit(int j, vector<int> now, int cnt, int bi){
	if (bi >= can[j].size()){
		int nmask = 0;
		for (int i = m; i >= 1; i--){
			if (now[i] >= 3) return;
			nmask *= 3;
			nmask += now[i];
		}
		dp[nmask][j] = min(dp[nmask][j], cnt);
		return;
	}

	transit(j, now, cnt, bi + 1);
	for (int i = 0; i < 3; i++){
		int idx = can[j][bi].first + i;
		if (idx > m) break;
		now[idx] = 0;
	}
	transit(j, now, cnt + 1, bi + 1);
}

void build_dp(){
	powv = 1;
	for (int i = 0; i < m; i++){
		powv *= 3;
	}
	for (int mask = 0; mask < powv; mask++){
		for (int j = 0; j < usey.size(); j++){
			dp[mask][j] = INF;
		}
	}
	dp[0][0] = 0;

	for (int j = 0; j + 1 < usey.size(); j++){
		for (int mask = 0; mask < powv; mask++){
			if (dp[mask][j] >= INF) continue;

			vector<int> now(m + 1, 0);
			int tmp = mask;
			int ok = 1;

			for (int i = 1; i <= m; i++){
				now[i] = tmp % 3;
				tmp /= 3;
			}
			for (int i = 1; i <= m; i++){
				if (now[i] > 0){
					now[i] += usey[j + 1] - usey[j];
					if (now[i] >= 4){
						ok = 0;
					}
				}
			}
			if (ok == 0) continue;

			for (int i = 1; i <= m; i++){
				if (now[i] == 0 && arr[i][j + 1] == 1){
					now[i] = 1;
				}
			}

			transit(j + 1, now, dp[mask][j], 0);
		}
	}
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int ans;
		scanf("%d %d %d", &m, &n, &p);

		for (int i = 0; i < m + 5; i++){
			for (int j = 0; j < p + 5; j++){
				arr[i][j] = 0;
				can[j].clear();
			}
		}
		usey.clear();
		po.clear();

		usey.push_back(0);
		for (int i = 0; i < p; i++){
			int x, y;
			scanf("%d %d", &x, &y);
			po.push_back({ x, y });
			usey.push_back(y);
		}
		compress();
		build_can();
		build_dp();

		printf("Case #%d\n", test);
		ans = dp[0][usey.size() - 1];
		if (ans >= INF) printf("-1\n");
		else printf("%d\n", ans);
	}

	return 0;
}
