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

int a[1010];
int b[1010];


int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++){
		scanf("%d %d", &a[i], &b[i]);
	}

	for (int i = 0; i < m; i++){
		int x, y, t;
		int ans = 0;
		scanf("%d %d %d", &x, &y, &t);

		for (int j = 0; j < n; j++){
			int len = abs(a[j] - b[j]);
			int now;

			if (a[j] < b[j]){
				if ((t / len) % 2 == 0) now = a[j] + t % len;
				else now = b[j] - t % len;
			}
			else{
				if ((t / len) % 2 == 0) now = a[j] - t % len;
				else now = b[j] + t % len;
			}
			if (x <= now && now <= y){
				ans++;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
