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
const ll INF = 5e18;
const int MOD = 1e9 + 7;

vector< pair<ll, ll> > dots;
ll adj[1010][1010];

ll dist1[1010];
ll dist2[1010];

void dijk(int start, ll dist[], int n){
	vector<int> visit(n, 0);
	for (int i = 0; i < n; i++){
		dist[i] = INF;
	}
	dist[start] = 0;
	
	while (1){
		int now = -1;
		ll minv = INF;
		for (int i = 0; i < n; i++){
			if (visit[i]) continue;
			if (minv > dist[i]){
				minv = dist[i];
				now = i;
			}
		}
		if (now == -1) break;
		visit[now] = 1;
		for (int nxt = 0; nxt < n; nxt++){
			dist[nxt] = min(dist[nxt], max(dist[now], adj[now][nxt]));
		}
	}
}

int main()
{
	int w, n;
	ll minv;
	int ans1, ans2;
	double mx, my;

	scanf("%d %d", &w, &n);
	dots = vector< pair<ll, ll> >(n + 2);
	for (int i = 1; i <= n; i++){
		scanf("%lld %lld", &dots[i].first, &dots[i].second);
	}
	dots[0] = { 0, 0 };
	dots[n + 1] = { w, 0 };

	for (int i = 0; i < n + 2; i++){
		for (int j = i + 1; j < n + 2; j++){
			if (i == 0){
				adj[i][j] = dots[j].first * dots[j].first * 4;
			}
			else if (j == n + 1){
				adj[i][j] = (w - dots[i].first) * (w - dots[i].first) * 4;
			}
			else{
				adj[i][j] = (dots[i].first - dots[j].first) * (dots[i].first - dots[j].first)
					+ (dots[i].second - dots[j].second) * (dots[i].second - dots[j].second);
				adj[i][j] *= 4;
			}
			adj[j][i] = adj[i][j];
		}
	}

	dijk(0, dist1, n + 2);
	dijk(n + 1, dist2, n + 2);

	minv = INF;
	ans1 = ans2 = -1;
	for (int i = 0; i < n + 2; i++){
		for (int j = 0; j < n + 2; j++){
			if (i == j) continue;

			ll maxv = max({ dist1[i], adj[i][j] / 4, dist2[j] });
			if (minv > maxv){
				minv = maxv;
				ans1 = i;
				ans2 = j;
			}
		}
	}
	mx = (double)(dots[ans1].first + dots[ans2].first) / 2;
	my = (double)(dots[ans1].second + dots[ans2].second) / 2;
	printf("%lf %lf\n", mx, my);
	return 0;
}
