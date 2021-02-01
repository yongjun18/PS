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

int sqrtv;
int arr[100100];
int cnt[100100];
int memb[100100];

struct Query{
	int l, r, idx;
	bool operator < (const Query &rhs) const{
		if (l / sqrtv != rhs.l / sqrtv) return l / sqrtv < rhs.l / sqrtv;
		return r < rhs.r;
	}
};

vector<Query> qry;
int ans[100100];

int main()
{
	int n, m;
	int l, r, maxcnt;

	scanf("%d", &n);
	sqrtv = (int)sqrt(n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int l, r;
		scanf("%d %d", &l, &r); l--; r--;
		qry.push_back({ l, r, i });
	}
	sort(qry.begin(), qry.end());

	memb[0] = 100100;
	maxcnt = 0;
	l = qry[0].l;
	r = qry[0].r;
	for (int i = l; i <= r; i++){
		memb[cnt[arr[i]]]--;
		cnt[arr[i]]++;
		memb[cnt[arr[i]]]++;

		if (memb[maxcnt + 1] > 0){
			maxcnt++;
		}
	}
	ans[qry[0].idx] = maxcnt;

	for (int i = 1; i < m; i++){
		while (qry[i].l < l){
			l--;
			memb[cnt[arr[l]]]--;
			cnt[arr[l]]++;
			memb[cnt[arr[l]]]++;
			if (memb[maxcnt + 1] > 0) maxcnt++;
			if (memb[maxcnt] == 0) maxcnt--;
		}
		while (l < qry[i].l){
			memb[cnt[arr[l]]]--;
			cnt[arr[l]]--;
			memb[cnt[arr[l]]]++;
			l++;
			if (memb[maxcnt + 1] > 0) maxcnt++;
			if (memb[maxcnt] == 0) maxcnt--;
		}
		while (r < qry[i].r){
			r++;
			memb[cnt[arr[r]]]--;
			cnt[arr[r]]++;
			memb[cnt[arr[r]]]++;
			if (memb[maxcnt + 1] > 0) maxcnt++;
			if (memb[maxcnt] == 0) maxcnt--;
		}
		while (qry[i].r < r){
			memb[cnt[arr[r]]]--;
			cnt[arr[r]]--;
			memb[cnt[arr[r]]]++;
			r--;
			if (memb[maxcnt + 1] > 0) maxcnt++;
			if (memb[maxcnt] == 0) maxcnt--;
		}
		ans[qry[i].idx] = maxcnt;
	}

	for (int i = 0; i < m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
