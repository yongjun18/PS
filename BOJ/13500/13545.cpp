#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MEM = 100100;
const int MX = 100100;

int n;
int sqrtn;
int arr[100100];
int psum[100100];

int cnt[100100];
int pcnt[400];
list<int> memb[200200];

struct Query{
	int l, r, idx;
	bool operator <(const Query& rhs) const{
		if (l / sqrtn != rhs.l / sqrtn) {
			return l / sqrtn < rhs.l / sqrtn;
		}
		return r < rhs.r;
	}
};

vector<Query> qry;
int ans[100100];

void update(int x, int val){
	cnt[x] += val;
	pcnt[x / sqrtn] += val;
}
int query(){
	for (int i = n / sqrtn; i >= 0; i--){
		if (pcnt[i] > 0){
			for (int j = min((i + 1) * sqrtn - 1, MX - 1); j >= 0; j--){
				if (cnt[j] > 0){
					return j;
				}
			}
		}
	}
	return 0;
}

int main()
{
	int m;
	int l, r;

	scanf("%d", &n);
	sqrtn = sqrt(n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &arr[i]);
		psum[i] = psum[i - 1] + arr[i];
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		qry.push_back({ x, y, i });
	}
	sort(qry.begin(), qry.end());

	l = qry[0].l;
	r = qry[0].r;
	for (int i = l - 1; i <= r; i++){
		int v = psum[i];
		if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), -1);
		memb[MEM + v].push_back(i);
		if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), 1);
	}
	ans[qry[0].idx] = query();

	for (int i = 1; i < m; i++){
		while (qry[i].l < l){
			l--;
			int v = psum[l - 1];
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), -1);
			memb[MEM + v].push_front(l - 1);
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), 1);
		}
		while (r < qry[i].r){
			r++;
			int v = psum[r];
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), -1);
			memb[MEM + v].push_back(r);
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), 1);
		}
		while (l < qry[i].l){
			int v = psum[l - 1];
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), -1);
			memb[MEM + v].pop_front();
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), 1);
			l++;
		}
		while (qry[i].r < r){
			int v = psum[r];
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), -1);
			memb[MEM + v].pop_back();
			if (memb[MEM + v].size() >= 2) update(memb[MEM + v].back() - memb[MEM + v].front(), 1);
			r--;
		}
		ans[qry[i].idx] = query();
	}
	for (int i = 0; i < m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
