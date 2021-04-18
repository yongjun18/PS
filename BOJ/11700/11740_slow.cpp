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
const int INF = 1e9;
const int MOD = 1e9 + 7;

ll w;
int n;

vector< pair<ll, ll> > pts;
int visit[1010][2];
pair<int, int> pv[1010][2];

ll distv(int i1, int i2){
	return (pts[i1].first - pts[i2].first) * (pts[i1].first - pts[i2].first) 
		+ (pts[i1].second - pts[i2].second) * (pts[i1].second - pts[i2].second);
}
void print_ans(int idx, int used){
	while (idx != -1){
		int pidx = pv[idx][used].first;
		int pused = pv[idx][used].second;
		if (used == 1 && pused == 0){
			if (pidx == -1){
				printf("%lf %lld\n", (double)pts[idx].first / 2, pts[idx].second);
			}
			else{
				printf("%lf %lf\n", (double)(pts[idx].first + pts[pidx].first) / 2, (double)(pts[idx].second + pts[pidx].second) / 2);
			}
			break;
		}
		idx = pidx;
		used = pused;
	}
}
int solve(ll x, int print){
	queue< pair<int, int> > q;

	for (int i = 0; i < n; i++){
		visit[i][0] = visit[i][1] = 0;
		pv[i][0] = pv[i][1] = { -1, 0 };
	}

	for (int i = 0; i < n; i++){
		if (4 * pts[i].first * pts[i].first <= x){
			visit[i][0] = 1;
			q.push({ i, 0 });
		}
		if (pts[i].first * pts[i].first <= x){
			visit[i][1] = 1;
			q.push({ i, 1 });
		}
	}

	while (q.size()){
		int idx = q.front().first;
		int used = q.front().second;
		q.pop();

		for (int nxt = 0; nxt < n; nxt++){
			if (nxt == idx) continue;

			if (distv(idx, nxt) * 4 <= x && visit[nxt][used] == 0){
				visit[nxt][used] = 1;
				q.push({ nxt, used });
				pv[nxt][used] = { idx, used };
			}
			if (used == 0 && distv(idx, nxt) <= x && visit[nxt][1] == 0){
				visit[nxt][1] = 1;
				q.push({ nxt, 1 });
				pv[nxt][1] = { idx, used };
			}
		}
	}
	for (int i = 0; i < n; i++){
		if (x >= 4 * (w - pts[i].first) * (w - pts[i].first)){
			if (visit[i][0]){
				if (print){
					printf("%.lf %lld\n", pts[i].first + 0.5, pts[i].second);
				}
				return 1;
			}
			if (visit[i][1]){
				if (print){
					print_ans(i, 1);
				}
				return 1;
			}
		}
		if (x >= (w - pts[i].first) * (w - pts[i].first)){
			if (visit[i][0]){
				if (print) {
					printf("%.lf %lld\n", (double)(w + pts[i].first) / 2, pts[i].second);
				}
				return 1;
			}
		}
	}
	return 0;
}
ll psearch(ll x, ll y){
	ll lo = x - 1;
	ll hi = y + 1;
	while (lo + 1 < hi){
		ll mid = (lo + hi) / 2;
		if (solve(mid, 0)) hi = mid;
		else lo = mid;
	}
	return hi;
}

int main()
{
	ll res;

	scanf("%lld %d", &w, &n);
	for (int i = 0; i < n; i++){
		ll x, y;
		scanf("%lld %lld", &x, &y);
		pts.push_back({ x, y });
	}

	if (n == 0){
		printf("%lf 0\n", (double)w / 2);
		return 0;
	}

	res = psearch(1, (ll)4e18);
	solve(res, 1);
	return 0;
}
