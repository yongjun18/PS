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

const int SUIT = 100100;

vector<int> subs;
int LIS(vector<int>& arr) {
	vector<int> num, idx;
	vector<int> prev(arr.size(), -1);
	subs.clear();

	for (int i = 0; i < arr.size(); i++) {
		int pos;
		pos = lower_bound(num.begin(), num.end(), arr[i]) - num.begin();

		if (pos == num.size()) {
			num.push_back(arr[i]);
			idx.push_back(i);
		}
		else {
			num[pos] = arr[i];
			idx[pos] = i;
		}
		if (pos == 0) prev[i] = -1;
		else prev[i] = idx[pos - 1];
	}

	for (int i = idx[idx.size() - 1]; i != -1; i = prev[i])
		subs.push_back(arr[i]);
	reverse(subs.begin(), subs.end());

	return subs.size();
}

int rankk[60];
int suit[60];
vector<int> order;
int inc[4];
vector<int> vec;

int main()
{
	int n;
	int ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		char r, s;
		scanf(" %c%c", &r, &s);

		rankk[i] = r - '0';
		if (r == 'T') rankk[i] = 10;
		if (r == 'J') rankk[i] = 11;
		if (r == 'Q') rankk[i] = 12;
		if (r == 'K') rankk[i] = 13;
		if (r == 'A') rankk[i] = 14;

		if (s == 's') suit[i] = 0;
		if (s == 'h') suit[i] = 1;
		if (s == 'd') suit[i] = 2;
		if (s == 'c') suit[i] = 3;
	}

	ans = INF;
	for (int i = 0; i < 5; i++) order.push_back(i);

	while (1) {
		for (inc[0] = 0; inc[0] < 2; inc[0]++) {
			for (inc[1] = 0; inc[1] < 2; inc[1]++) {
				for (inc[2] = 0; inc[2] < 2; inc[2]++) {
					for (inc[3] = 0; inc[3] < 2; inc[3]++) {
						
						int res;
						vec.clear();
						for (int i = 0; i < n; i++) {
							int nrank = rankk[i];
							if (inc[suit[i]] == 0) nrank *= -1;
							vec.push_back(order[suit[i]] * SUIT + nrank);
						}
						res = LIS(vec);
						ans = min(ans, n - res);
					}
				}
			}
		}
		if (next_permutation(order.begin(), order.end()) == 0) break;
	}

	printf("%d\n", ans);
	return 0;
}
