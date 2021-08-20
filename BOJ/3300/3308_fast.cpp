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

int idx[1000100];
int pv[1000100];
int nxt[1000100];

int fail[1000100];
vector<int> ans;

void build(){
	for (int i = 0; i < n; i++){
		idx[s[i]] = i;
	}
	pv[idx[0]] = -1;
	nxt[idx[0]] = idx[1];
	for (int i = 1; i <= n - 2; i++){
		pv[idx[i]] = idx[i - 1];
		nxt[idx[i]] = idx[i + 1];
	}
	pv[idx[n - 1]] = idx[n - 2];
	nxt[idx[n - 1]] = -1;

	for (int i = n - 1; i >= 0; i--){
		if (pv[i] != -1) nxt[pv[i]] = nxt[i];
		if (nxt[i] != -1) pv[nxt[i]] = pv[i];
	}
}

int check(int arr[], int match, int last){
	return ((pv[match] == -1 || arr[last - match + pv[match]] < arr[last])
		&& (nxt[match] == -1 || arr[last - match + nxt[match]] > arr[last]));
}

void build_fail(){
	int match = 0;
	for (int last = 1; last < n; last++){
		while (match > 0 && check(s, match, last) == 0)
			match = fail[match - 1];
		if (check(s, match, last)) match++;
		fail[last] = match;
	}
}

void kmp(){
	int match = 0;
	for (int last = 0; last < m; last++){
		while (match > 0 && check(h, match, last) == 0)
			match = fail[match - 1];
		if (check(h, match, last)) match++;
		if (match == n){
			ans.push_back(last - match + 1);
			match = fail[match - 1];
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

	build();
	build_fail();
	kmp();

	printf("%d\n", ans.size());
	for (int it : ans) printf("%d ", it + 1);
	printf("\n");

	return 0;
}
