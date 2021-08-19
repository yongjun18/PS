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

int n, m;
int s[1000100];
int h[1000100];

int s2[1000100];
int fail[1000100];
vector<int> ans;

const int MX = 1000100;
ll tree[2 * MX];

void init() {
	for (int i = 0; i < MX; i++)
		tree[MX + i] = 0;
	for (int i = MX - 1; i > 0; i--)
		tree[i] = tree[i << 1] + tree[i << 1 | 1];
}
void update(int idx, ll val) {
	for (tree[idx += MX] += val; idx > 1; idx >>= 1)
		tree[idx >> 1] = tree[idx] + tree[idx ^ 1];
}
ll query(int l, int r) {
	ll res = 0;
	for (l += MX, r += MX; l < r; l >>= 1, r >>= 1){
		if (l & 1) res += tree[l++];
		if (r & 1) res += tree[--r];
	}
	return res;
}

void compress(){
	vector<int> used;
	for (int i = 0; i < m; i++){
		used.push_back(h[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < m; i++){
		h[i] = lower_bound(used.begin(), used.end(), h[i]) - used.begin();
	}
}

void build_fail(){
	int match = 0;
	int from = 1;

	init();
	for (int i = 0; i < n; i++){
		s2[i] = query(0, s[i]);
		update(s[i], 1);
	}

	init();
	for (int last = 1; last < n; last++){
		while (match > 0 && query(0, s[last]) != s2[match]){
			match = fail[match - 1];
			while (last - from > match){
				update(s[from], -1);
				from++;
			}
		}
		if (query(0, s[last]) == s2[match]){
			match++;
			update(s[last], 1);
		}
		fail[last] = match;
	}
}

void get_ans(){
	int match = 0;
	int from = 0;

	init();
	for (int last = 0; last < m; last++){
		while (match > 0 && query(0, h[last]) != s2[match]){
			match = fail[match - 1];
			while (last - from > match){
				update(h[from], -1);
				from++;
			}
		}
		if (query(0, h[last]) == s2[match]){
			match++;
			update(h[last], 1);
		}
		if (match == n){
			ans.push_back(last - match + 1);
			match = fail[match - 1];
			while (last + 1 - from > match){
				update(h[from], -1);
				from++;
			}
		}
	}
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		s[x - 1] = i;
	}
	for (int i = 0; i < m; i++){
		scanf("%d", &h[i]);
	}
	compress();

	build_fail();
	get_ans();

	printf("%d\n", ans.size());
	for (int it : ans){
		printf("%d ", it + 1);
	}
	printf("\n");

	return 0;
}
