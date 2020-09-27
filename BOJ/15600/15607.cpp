#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct App{
	int num, d, s;
	bool operator < (const App& rhs) const{
		return s-d < rhs.s-rhs.d;
	}
};

vector<App> apps;
int dp[505][10100];
int chosen[505][10100];
vector<int> ans;

void get_ans(int i, int nowc){
	if(i <= 0) return;

	if(chosen[i][nowc] == 1){
		ans.push_back(apps[i].num);
		get_ans(i-1, nowc - apps[i].s);
	}
	else{
		get_ans(i-1, nowc);
	}
}

int main()
{
	int n, c;
	int maxv;

	scanf("%d %d", &n, &c);
	apps.resize(n+1);
	for(int i=1; i<=n; i++){
		apps[i].num = i;
		scanf("%d %d", &apps[i].d, &apps[i].s);
	}
	sort(apps.begin()+1, apps.end());

	for(int i=0; i<n; i++){
		for(int nowc=0; nowc<=c; nowc++){
			if(dp[i+1][nowc] < dp[i][nowc]){
				dp[i+1][nowc] = dp[i][nowc];
				chosen[i+1][nowc] = 0;
			}
			if(nowc + max(apps[i+1].d, apps[i+1].s) <= c){
				int nxtc = nowc + apps[i+1].s;
				if(dp[i+1][nxtc] < dp[i][nowc] + 1){
					dp[i+1][nxtc] = dp[i][nowc] + 1;
					chosen[i+1][nxtc] = 1;
				}
			}
		}
	}

	maxv = 0;
	for(int nowc=0; nowc<=c; nowc++){
		maxv = max(maxv, dp[n][nowc]);
	}
	printf("%d\n", maxv);

	for(int nowc=0; nowc<=c; nowc++){
		if(dp[n][nowc] == maxv){
			get_ans(n, nowc);
			reverse(ans.begin(), ans.end());

			for(int it : ans) printf("%d ", it);
			printf("\n");
			break;
		}
	}
	return 0;
}
