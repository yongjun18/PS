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

int pushed[370];

int main()
{
	int n;
	int dirty, cnt, ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int d;
		scanf("%d", &d);
		pushed[d] = 1;
	}
	
	dirty = 0;
	cnt = 0;
	ans = 0;
	for (int i = 1; i <= 370; i++){
		if (dirty + cnt >= 20){
			ans++;
			cnt = 0;
			dirty = 0;
		}
		dirty += cnt;
		if (pushed[i]){
			cnt++;
		}
	}
	if (dirty > 0){
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
