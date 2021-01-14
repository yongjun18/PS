#include <stdio.h>
#include <set>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int fr[1050];
int to[1050];
int nxt[1050];
int held[1050];
set<int> used;

vector<int> ans;

int find_empty(int x){
	for (int i = fr[x] + 1; i < to[x]; i++){
		if (used.count(i) == 0){
			return i;
		}
	}
	return -1;
}

int main()
{
	int n, p;
	int ok;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d %d", &fr[i], &to[i]);
	}
	for (int i = 0; i + 1 < n; i++){
		if (to[i] == fr[i + 1]){
			nxt[i] = 1;
		}
	}

	ok = 1;
	scanf("%d", &p);
	while (p--){
		int x;
		scanf("%d", &x);
		used.insert(x);
		for (int i = 0; i < n; i++){
			if (fr[i] <= x && x <= to[i]){
				held[i]++;
				if (held[i] > 2) ok = 0;
			}
		}
	}

	if (ok == 0){
		printf("impossible\n");
	}
	else{
		for (int i = 0; i < n; i++){
			while (held[i] < 2){
				if (i + 1 < n && nxt[i] && held[i + 1] < 2 && used.count(to[i]) == 0){
					ans.push_back(to[i]);
					used.insert(to[i]);
					held[i]++;
					held[i + 1]++;
				}
				else{
					int newp = find_empty(i);
					ans.push_back(newp);
					used.insert(newp);
					held[i]++;
				}
			}
		}
		printf("%d\n", ans.size());
		for (int it : ans){
			printf("%d ", it);
		}
		printf("\n");
	}

	return 0;
}
