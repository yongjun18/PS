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

char str[50100];
char ans[50100];

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n, m;

		scanf("%d %d", &n, &m);
		scanf("%s", str);
		for (int i = 0; i < n; i++){
			ans[i] = '0';
		}
		ans[n] = 0;

		for (int i = 0; i < n; i++){
			if (str[i] == '0') continue;
			if (i - m >= 0 && ans[i - m] == '1') continue;
			
			if (i + m < n && (i + m + m >= n || str[i + m + m] == '1')){
				ans[i + m] = '1';
			}
			else{
				ans[i - m] = '1';
			}
		}

		printf("Case #%d\n", test);
		printf("%s\n", ans);
	}

	return 0;
}
