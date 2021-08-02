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



int main()
{
	int a, d, k;
	double cnt, now, win;

	scanf("%d %d %d", &a, &d, &k);

	cnt = 0;
	now = 1;
	win = (double)d / 100;
	
	for (int i = 1;; i++){
		cnt += now * min(win, 1.0) * i;
		if (win >= 1.0) break;
		now *= (1 - win);
		win *= (double)(100 + k) / 100;
	}
	
	printf("%.9lf\n", cnt * a);
	return 0;
}
