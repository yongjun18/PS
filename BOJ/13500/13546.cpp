#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <string.h>
#include <string>
#include <math.h>
#include <list>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 100100;
int n;
int sqrtn;
int arr[100100];

list<int> appear[100100];

int k;
int cnt[100100];
int pcnt[319];

void update(int idx, int val){
	cnt[idx] += val;
	pcnt[idx / sqrtn] += val;
}
int query(){
	for (int i = n / sqrtn; i >= 0; i--){
		if (pcnt[i] > 0){
			for (int j = min(MX - 1, (i + 1) * sqrtn - 1); j >= 0; j--){
				if (cnt[j] > 0){
					return j;
				}
			}
		}
	}
	return 0;
}

struct Query{
	int l, r, idx;
	bool operator < (const Query &rhs) const{
		if (l / sqrtn != rhs.l / sqrtn) return l / sqrtn < rhs.l / sqrtn;
		return r < rhs.r;
	}
};

vector<Query> qry;
int ans[100100];

int main()
{
	int m;
	int l, r;

	scanf("%d %d", &n, &k);
	sqrtn = sqrt(n);
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

	l = qry[0].l;
	r = qry[0].r;
	for (int i = l; i <= r; i++){
		int v = arr[i];
		if (appear[v].size() > 0){
			update(appear[v].back() - appear[v].front(), -1);
		}
		appear[v].push_back(i);
		update(appear[v].back() - appear[v].front(), 1);
	}
	ans[qry[0].idx] = query();

	for (int i = 1; i < m; i++){
		while (qry[i].l < l){
			l--;
			int v = arr[l];
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), -1);
			}
			appear[v].push_front(l);
			update(appear[v].back() - appear[v].front(), 1);
		}
		while (r < qry[i].r){
			r++;
			int v = arr[r];
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), -1);
			}
			appear[v].push_back(r);
			update(appear[v].back() - appear[v].front(), 1);
		}
		while (l < qry[i].l){
			int v = arr[l];
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), -1);
			}
			appear[v].pop_front();
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), 1);
			}
			l++;
		}
		while (qry[i].r < r){
			int v = arr[r];
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), -1);
			}
			appear[v].pop_back();
			if (appear[v].size() > 0){
				update(appear[v].back() - appear[v].front(), 1);
			}
			r--;
		}
		ans[qry[i].idx] = query();
	}

	for (int i = 0; i < m; i++){
		printf("%d\n", ans[i]);
	}
	return 0;
}
