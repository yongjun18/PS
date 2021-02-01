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

int sqrtv = 316;
ll arr[100100];
ll cnt[1000100];

struct Query{
	int l, r, idx;
	bool operator < (const Query &rhs) const{
		if (l / sqrtv != rhs.l / sqrtv) return l / sqrtv < rhs.l / sqrtv;
		return r < rhs.r;
	}
};

vector<Query> qry;
ll ans[100100];

int main()
{
	int n, t;
	int l, r;
	ll nowv;

	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; i++){
		scanf("%lld", &arr[i]);
	}
	for (int i = 0; i < t; i++){
		int l, r;
		scanf("%d %d", &l, &r); l--; r--;
		qry.push_back({ l, r, i });
	}
	sort(qry.begin(), qry.end());

	l = qry[0].l;
	r = qry[0].r;
	nowv = 0;
	for (int i = l; i <= r; i++){
		nowv -= cnt[arr[i]] * cnt[arr[i]] * arr[i];
		cnt[arr[i]]++;
		nowv += cnt[arr[i]] * cnt[arr[i]] * arr[i];
	}
	ans[qry[0].idx] = nowv;

	for (int i = 1; i < t; i++){
		while (l < qry[i].l){
			nowv -= cnt[arr[l]] * cnt[arr[l]] * arr[l];
			cnt[arr[l]]--;
			nowv += cnt[arr[l]] * cnt[arr[l]] * arr[l];
			l++;
		}
		while (qry[i].l < l){
			l--;
			nowv -= cnt[arr[l]] * cnt[arr[l]] * arr[l];
			cnt[arr[l]]++;
			nowv += cnt[arr[l]] * cnt[arr[l]] * arr[l];
		}
		while (qry[i].r < r){
			nowv -= cnt[arr[r]] * cnt[arr[r]] * arr[r];
			cnt[arr[r]]--;
			nowv += cnt[arr[r]] * cnt[arr[r]] * arr[r];
			r--;
		}
		while (r < qry[i].r){
			r++;
			nowv -= cnt[arr[r]] * cnt[arr[r]] * arr[r];
			cnt[arr[r]]++;
			nowv += cnt[arr[r]] * cnt[arr[r]] * arr[r];
		}
		ans[qry[i].idx] = nowv;
	}
	
	for (int i = 0; i < t; i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
