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
const ll INF = 1.1e18;
const int MOD = 1e9 + 7;

int minf[1000001];
vector<int> prime;
vector<string> str;

ll l, r;

ll dp1[500][2805];
ll dp2[500][2805];
vector<int> now;

void dfs(ll nowlen, int i, int sum){
	if (r < 0) return;
	if (sum < 0) return;
	if (dp1[i][sum] == 0) return;

	ll tmp;
	if ((double)nowlen * dp1[i][sum] + dp2[i][sum] > INF)
		tmp = INF;
	else tmp = min(INF, nowlen * dp1[i][sum] + dp2[i][sum]);

	if (tmp < l){
		l -= tmp;
		r -= tmp;
		return;
	}
	if (sum == 0){
		string ret = "[";
		for (int i = 0; i < now.size(); i++){
			ret += str[now[i]] + ", ";
		}
		ret.pop_back(); ret.pop_back();
		ret += "], ";

		for (int i = max(l, 0ll); i <= min(r, tmp - 1); i++){
			printf("%c", ret[i]);
		}
		l -= tmp;
		r -= tmp;
		return;
	}

	now.push_back(i);
	dfs(nowlen + str[i].size() + 2, i + 1, sum - prime[i]);
	now.pop_back();
	dfs(nowlen, i + 1, sum);
}

void build_dp(){
	int ps = prime.size();
	dp1[ps - 1][0] = 1;
	dp2[ps - 1][0] = 0;
	for (int i = ps - 2; i >= 0; i--){
		for (int j = 0; j <= 2800; j++){
			if (j - prime[i] >= 0){
				dp1[i][j] = dp1[i + 1][j - prime[i]];
				dp2[i][j] = dp2[i + 1][j - prime[i]] + (str[i].size() + 2) * dp1[i + 1][j - prime[i]];
			}
			dp1[i][j] += dp1[i + 1][j];
			dp2[i][j] += dp2[i + 1][j];

			dp1[i][j] = min(dp1[i][j], INF);
			dp2[i][j] = min(dp2[i][j], INF);
		}
	}
}

void build_str(int x){
	string ret;
	while (x > 0){
		ret.push_back((x % 10) + '0');
		x /= 10;
	}
	reverse(ret.begin(), ret.end());
	str.push_back(ret);
}
void eratos(int n) {
	minf[0] = minf[1] = -1;
	for (int i = 2; i <= n; i++) minf[i] = i;

	for (int i = 2; i*i <= n; i++) {
		if (minf[i] == i) {
			for (int j = i*i; j <= n; j += i) {
				if (minf[j] == j) minf[j] = i;
			}
		}
	}
	for (int i = 2; i <= n; i++){
		if (minf[i] == i){
			prime.push_back(i);
			build_str(i);
		}
	}
}

int main()
{
	scanf("%lld %lld", &l, &r);
	l--; r--;

	eratos(2800);
	build_dp();

	for (int sum = 1; sum <= 2800; sum++){
		dfs(2, 0, sum);
	}
	printf("\n");
	return 0;
}
