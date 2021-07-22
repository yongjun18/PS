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

struct QNode{
	int x, y;
	ll amount;
	bool operator < (const QNode& rhs) const{
		return amount < rhs.amount;
	}
};

int arr[505][505];
int visit[505][505];
priority_queue<QNode> pq;

int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

int main()
{
	int n, m;
	int i, j;
	ll ans;

	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			scanf("%d", &arr[i][j]);
		}
	}
	scanf("%d %d", &i, &j);

	ans = -arr[i][j];
	visit[i][j] = 1;
	pq.push({ i, j, -arr[i][j] });

	while (pq.size()){
		int x = pq.top().x;
		int y = pq.top().y;
		ll amount = pq.top().amount;
		pq.pop();

		for (int d = 0; d < 8; d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (visit[nx][ny]) continue;
			ll nxta = min(amount, -(ll)arr[nx][ny]);
			if (nxta <= 0) continue;

			ans += nxta;
			visit[nx][ny] = 1;
			pq.push({ nx, ny, nxta });
		}
	}
	printf("%lld\n", ans);
	return 0;
}
