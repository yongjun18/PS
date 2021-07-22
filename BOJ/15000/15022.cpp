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
typedef long long ll;

vector< pair<int, int> > events;
int sol[100100];
int pen[100100];

vector< pair<int, int> > used;
int cnt[100100];

int get_idx(int s, int p){
	pair<int, int> tmp = { s, -p };
	return lower_bound(used.begin(), used.end(), tmp) - used.begin();
}

int main()
{
	int n, m;
	int rank1, now1;

	scanf("%d %d", &n, &m);

	events.resize(m);
	for (int i = 0; i < m; i++){
		scanf("%d %d", &events[i].first, &events[i].second);
	}

	used.push_back({ 0, 0 });
	for (int i = 0; i < m; i++){
		int t = events[i].first;
		int p = events[i].second;
		sol[t]++;
		pen[t] += p;
		used.push_back({ sol[t], -pen[t] });
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	cnt[0] = n;
	rank1 = 1;
	now1 = 0;
	memset(sol, 0, sizeof(sol));
	memset(pen, 0, sizeof(pen));

	for (int i = 0; i < m; i++){
		int t = events[i].first;
		int p = events[i].second;
		
		if (t == 1){
			sol[1]++;
			pen[1] += p;
			int nxt1 = get_idx(sol[1], pen[1]);
			cnt[now1]--;
			while (now1 < nxt1){
				rank1 -= cnt[now1 + 1];
				now1++;
			}
			cnt[now1]++;
		}
		else{
			int now, nxt;

			now = get_idx(sol[t], pen[t]);
			sol[t]++;
			pen[t] += p;
			nxt = get_idx(sol[t], pen[t]);
			cnt[now]--;
			cnt[nxt]++;
			if (now <= now1 && now1 < nxt){
				rank1++;
			}
		}
		printf("%d\n", rank1);
	}
	return 0;
}
