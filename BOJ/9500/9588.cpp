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

const int MX = 1001000;
ll tree[MX * 4];
ll query(int l, int r, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return -INF;
	if (l <= nl && nr <= r) return tree[no];
	int mid = (nl + nr) / 2;
	return max(query(l, r, 2 * no, nl, mid), query(l, r, 2 * no + 1, mid, nr));
}
ll query(int l, int r, int n) { return query(l, r, 1, 0, n); }
ll update(int idx, ll val, int no, int nl, int nr) {
	if (idx < nl || nr <= idx) return tree[no];
	if (nl + 1 == nr && nl == idx) return tree[no] += val;
	int mid = (nl + nr) / 2;
	return tree[no] = max(update(idx, val, 2 * no, nl, mid), update(idx, val, 2 * no + 1, mid, nr));
}
ll update(int idx, ll val, int n) { return update(idx, val, 1, 0, n); }


int b[1001000];
int l[1001000];
int field[1001000];
vector<int> app[1001000];
vector<int> ans;

int main()
{
	int n, p, c, h;
	int oth;

	scanf("%d %d %d %d", &n, &p, &c, &h);
	for (int i = 0; i < n; i++){
		scanf("%d", &b[i]);
		app[b[i]].push_back(i);
		field[b[i]]++;
	}
	for (int i = 0; i < p; i++){
		scanf("%d", &l[i]);
	}

	if (n == 1){
		if (l[p - 1] == h) printf("1\n1 \n");
		else printf("0\n");
		return 0;
	}

	oth = 0;
	for (int i = 1; i < p; i++){
		if (l[i] != h){
			update(l[i], 1, MX);
			oth++;
		}
	}
	for (int i = 0; i < n; i++){
		if (b[i] != h){
			update(b[i], 1, MX);
		}
	}

	for (int i = 1; i <= c; i++){
		if (field[i] > 0){
			field[i]--;
			field[l[0]]++;
			if (i != h){
				update(i, -1, MX);
			}
			update(l[0], 1, MX);

			if (field[h] - oth > query(0, MX, MX)){
				for (int it : app[i]){
					ans.push_back(it + 1);
				}
			}

			field[i]++;
			field[l[0]]--;
			if (i != h){
				update(i, 1, MX);
			}
			update(l[0], -1, MX);
		}
	}
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int it : ans){
		printf("%d ", it);
	}
	if (ans.size() > 0){
		printf("\n");
	}
	return 0;
}
