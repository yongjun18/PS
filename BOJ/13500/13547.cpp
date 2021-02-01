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

const int sqrtv = 316;
int arr[100100];
int cnt[1000100];

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
	int l, r, dcnt;

	scanf("%d", &n);
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

	dcnt = 0;
	l = qry[0].l;
	r = qry[0].r;
	for (int i = l; i <= r; i++){
		if (cnt[arr[i]]++ == 0) dcnt++;
	}
	ans[qry[0].idx] = dcnt;

	for (int i = 1; i < m; i++){
		while (qry[i].l < l){
			if (cnt[arr[--l]]++ == 0) dcnt++;
		}
		while (r < qry[i].r){
			if (cnt[arr[++r]]++ == 0) dcnt++;
		}
		while (l < qry[i].l){
			if (--cnt[arr[l++]] == 0) dcnt--;
		}
		while (qry[i].r < r){
			if (--cnt[arr[r--]] == 0) dcnt--;
		}
		ans[qry[i].idx] = dcnt;
	}
	for (int i = 0; i < m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
