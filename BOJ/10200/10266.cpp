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

const int MOD = 360'000;
const int MX = 200100;

vector<int> get_fail(int m, int arr[]) {
	vector<int> fail(m, 0);
	int match = 0;
	for (int last = 1; last < m; last++) {
		while (match > 0 && arr[last] != arr[match])
			match = fail[match - 1];
		if (arr[last] == arr[match]) match++;
		fail[last] = match;
	}
	return fail;
}

vector<int> kmp(int n, int arr1[], int m, int arr2[]) {
	vector<int> ret;
	vector<int> fail = get_fail(m, arr2);

	int match = 0;
	for (int last = 0; last < n; last++) {
		while (match > 0 && arr1[last] != arr2[match])
			match = fail[match - 1];

		if (arr1[last] == arr2[match]) match++;
		if (match == m) {
			ret.push_back(last - match + 1);
			match = fail[match - 1];
		}
	}
	return ret;
}

int a[MX];
int b[MX];
int ta[MX * 2];
int tb[MX];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}
	sort(a, a + n);
	sort(b, b + n);

	for (int i = 0; i < n; i++) {
		int diff = a[i] - a[((i - 1) + n) % n];
		ta[i] = (diff + MOD) % MOD;
	}
	for (int i = n; i < 2 * n; i++) {
		ta[i] = ta[i - n];
	}
	for (int i = 0; i < n; i++) {
		int diff = b[i] - b[((i - 1) + n) % n];
		tb[i] = (diff + MOD) % MOD;
	}

	if (kmp(2 * n, ta, n, tb).size() > 0) {
		printf("possible\n");
	}
	else {
		printf("impossible\n");
	}
	return 0;
}
