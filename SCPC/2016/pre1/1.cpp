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

const int MX = 5001000;
int cnt[MX];
int ans[MX];

int memo(int x){
	int &ret = cnt[x];
	if (ret != -1) return ret;
	if (x == 1) return ret = 0;

	if (x % 2 == 0){
		ret = memo(x / 2) + 1;
	}
	else{
		ret = memo(3 * x + 1) + 1;
	}
	return ret;
}

void init(){
	memset(cnt, -1, sizeof(cnt));
	for (int i = 1; i < 3000; i++) memo(i);
	for (int i = 0; i < MX; i++) ans[i] = INF;

	for (int i = 1; i < MX; i++){
		ans[cnt[i]] = min(ans[cnt[i]], i);
	}
}

int main()
{
	int t;

	init();
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int k;
		scanf("%d", &k);
		printf("Case #%d\n", test);
		printf("%d %llu\n", ans[k], (1UL << k));
	}

	return 0;
}
