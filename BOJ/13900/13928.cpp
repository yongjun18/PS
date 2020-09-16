#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
char nums[45][405];

int dp[405][45][45][10];
int fix[405][45][45][10];
char ans[45][405];

int memo(int idx, int bg, int ed, int maxv){
	if(bg >= ed || idx >= m) return 0;
	if(maxv < 0) return INF;

	int &ret = dp[idx][bg][ed][maxv];
	if(ret != -1) return ret;

	int dif = 0;
	ret = memo(idx, bg, ed, maxv-1);
	for(int i=ed-1; i>=bg; i--){
		if(nums[i][idx] != '0' + maxv) dif++;
		int tmp = memo(idx, bg, i, maxv-1)
				+ memo(idx+1, i, ed, 9) + dif;
		if(ret > tmp){
			ret = tmp;
			fix[idx][bg][ed][maxv] = ed-i;
		}
	}
	return ret;
}

void get_ans(int idx, int bg, int ed, int maxv){
	if(bg >= ed || idx >= m || maxv < 0) return;

	int fixv = fix[idx][bg][ed][maxv];
	for(int i=0; i<fixv; i++)
		ans[ed-1-i][idx] = '0' + maxv;
	get_ans(idx, bg, ed-fixv, maxv-1);
	get_ans(idx+1, ed-fixv, ed, 9);
}

int main()
{
	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++)
		scanf("%s", nums[i]);

	memset(dp, -1, sizeof(dp));
	memo(0, 0, n, 9);
	get_ans(0, 0, n, 9);

	for(int i=0; i<n; i++)
		printf("%s\n", ans[i]);
	return 0;
}
