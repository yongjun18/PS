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

int ready;
queue<int> running;

int main()
{
	int n, k;
	int ans;

	scanf("%d %d", &n, &k);

	ans = 0;
	ready = 0;
	
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);

		while (running.size() > 0 && (x - running.front()) >= 1000) {
			running.pop();
			ready++;
		}

		if (ready == 0) {
			ready += k;
			ans++;
		}
		ready--;
		running.push(x);
	}
	printf("%d\n", ans);
	return 0;
}
