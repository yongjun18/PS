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

const int MX = 500100;
int mx;

ll tree[MX * 4];
ll lazy[MX * 4];

void init(){
	for (int i = 0; i < mx * 4; i++){
		tree[i] = lazy[i] = 0;
	}
}
void propagate(int no, int nl, int nr){
	if (nl + 1 < nr){
		tree[2 * no] += lazy[no];
		tree[2 * no + 1] += lazy[no];
		lazy[2 * no] += lazy[no];
		lazy[2 * no + 1] += lazy[no];
	}
	lazy[no] = 0;
}
ll update(int l, int r, ll val, int no, int nl, int nr){
	if (r <= nl || nr <= l) return tree[no];
	if (l <= nl && nr <= r){
		tree[no] += val;
		lazy[no] += val;
		return tree[no];
	}
	propagate(no, nl, nr);
	int mid = (nl + nr) / 2;
	return tree[no] = max(
		update(l, r, val, 2 * no, nl, mid),
		update(l, r, val, 2 * no + 1, mid, nr));
}
void update(int l, int r, ll val, int n = mx){ update(l, r, val, 1, 0, n); }

int n, k, m;
char str[50100];

vector<int> used;

int num(int x, int y){
	int ret = 0;
	for (int i = x; i <= y; i++){
		ret *= 10;
		ret += str[i] - '0';
	}
	return ret;
}

void get_used(){
	used.clear();
	for (int i = 0; i + k - 1 < n; i++){
		used.push_back(num(i, i + k - 1));
	}
	for (int i = 0; i < n; i++){
		char tmp = str[i];
		str[i] = '1';
		for (int j = max(0, i - k + 1); j + k - 1 < n; j++){
			used.push_back(num(j, j + k - 1));
		}
		str[i] = tmp;
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());
}

void update(int numv, int val){
	int l = lower_bound(used.begin(), used.end(), numv - m) - used.begin();
	int r = upper_bound(used.begin(), used.end(), numv) - used.begin();
	update(l, r, val);
}

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		ll ans;

		scanf("%d %d %d", &n, &k, &m);
		scanf("%s", str);

		get_used();
		mx = used.size() + 5;
		init();

		for (int i = 0; i + k - 1 < n; i++){
			update(num(i, i + k - 1), 1);
		}
		ans = tree[1];

		for (int i = 0; i < n; i++){
			for (int j = max(0, i - k + 1); j + k - 1 < n; j++){
				update(num(j, j + k - 1), -1);
			}
			char tmp = str[i];
			str[i] = '1';
			for (int j = max(0, i - k + 1); j + k - 1 < n; j++){
				update(num(j, j + k - 1), 1);
			}

			ans = max(ans, tree[1]);

			for (int j = max(0, i - k + 1); j + k - 1 < n; j++){
				update(num(j, j + k - 1), -1);
			}
			str[i] = tmp;
			for (int j = max(0, i - k + 1); j + k - 1 < n; j++){
				update(num(j, j + k - 1), 1);
			}
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
