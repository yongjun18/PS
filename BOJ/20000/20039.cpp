#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 500100;
struct SegTree{
	ll tree[2 * MX];

	void update(int idx, ll val) {
		tree[idx + MX] = max(tree[idx + MX], val);
		idx += MX;
		for (; idx > 1; idx >>= 1)
			tree[idx >> 1] = max(tree[idx], tree[idx ^ 1]);
	}

	ll query(int l, int r) {
		ll res = 0;
		for (l += MX, r += MX; l < r; l >>= 1, r >>= 1){
			if (l & 1) res = max(res, tree[l++]);
			if (r & 1) res = max(res, tree[--r]);
		}
		return res;
	}
};

SegTree inc2, inc3, dec2, dec3;

int arr[500100];

void compress(int n){
	vector<int> used;
	for (int i = 0; i < n; i++){
		used.push_back(arr[i]);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());

	for (int i = 0; i < n; i++){
		int pos = lower_bound(used.begin(), used.end(), arr[i]) - used.begin();
		arr[i] = pos + 1;
	}
}

int main()
{
	int n;
	int minv, maxv;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	compress(n);

	minv = INF;
	maxv = 0;

	for (int i = 0; i < n; i++){
		if (minv < arr[i]) inc2.update(arr[i], 2);
		if (maxv > arr[i]) dec2.update(arr[i], 2);

		int tmp = dec3.query(1, arr[i]);
		if (tmp > 0) inc2.update(arr[i], tmp + 1);

		tmp = max(inc2.query(1, arr[i]), inc3.query(1, arr[i]));
		if (tmp > 0) inc3.update(arr[i], tmp + 1);

		tmp = inc3.query(arr[i] + 1, MX);
		if (tmp > 0) dec2.update(arr[i], tmp + 1);

		tmp = max(dec2.query(arr[i] + 1, MX), dec3.query(arr[i] + 1, MX));
		if (tmp > 0) dec3.update(arr[i], tmp + 1);

		minv = min(minv, arr[i]);
		maxv = max(maxv, arr[i]);
	}
	printf("%lld\n", max(inc3.tree[1], dec3.tree[1]));

	return 0;
}
