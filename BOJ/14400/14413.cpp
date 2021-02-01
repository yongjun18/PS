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

int sqrtv = 707;
int arr[500100];
int cnt[500100];

struct Query{
	int l, r, idx;
	bool operator < (const Query& rhs) const{
		if (l / sqrtv != rhs.l / sqrtv) return l / sqrtv < rhs.l / sqrtv;
		return r < rhs.r;
	}
};

vector<Query> qry;
int ans[500100];

void compress(int n){
	vector<int> used;
	for (int i = 0; i < n; i++){
		used.push_back(arr[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < n; i++){
		int pos = lower_bound(used.begin(), used.end(), arr[i]) - used.begin();
		arr[i] = pos;
	}
}

int main()
{
	int n, q;
	int l, r, cnt2;

	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	compress(n);
	
	for (int i = 0; i < q; i++){
		int l, r;
		scanf("%d %d", &l, &r); l--; r--;
		qry.push_back({ l, r, i });
	}
	sort(qry.begin(), qry.end());

	l = qry[0].l;
	r = qry[0].r;
	cnt2 = 0;
	for (int i = l; i <= r; i++){
		cnt[arr[i]]++;
		if (cnt[arr[i]] == 2) cnt2++;
		if (cnt[arr[i]] == 3) cnt2--;
	}
	ans[qry[0].idx] = cnt2;

	for (int i = 1; i < q; i++){
		while (qry[i].l < l){
			l--;
			cnt[arr[l]]++;
			if (cnt[arr[l]] == 2) cnt2++;
			if (cnt[arr[l]] == 3) cnt2--;
		}
		while (l < qry[i].l){
			cnt[arr[l]]--;
			if (cnt[arr[l]] == 2) cnt2++;
			if (cnt[arr[l]] == 1) cnt2--;
			l++;
		}
		while (r < qry[i].r){
			r++;
			cnt[arr[r]]++;
			if (cnt[arr[r]] == 2) cnt2++;
			if (cnt[arr[r]] == 3) cnt2--;
		}
		while (qry[i].r < r){
			cnt[arr[r]]--;
			if (cnt[arr[r]] == 2) cnt2++;
			if (cnt[arr[r]] == 1) cnt2--;
			r--;
		}
		ans[qry[i].idx] = cnt2;
	}
	for (int i = 0; i < q; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
