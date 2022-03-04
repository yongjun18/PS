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

int arr[1000100];
multiset<int> st;
vector<int> ans;

int main()
{
	int n, m, c;
	int x, y;

	scanf("%d %d %d", &n, &m, &c);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}

	x = 1;
	y = m;
	for (int i = x; i <= y; i++) {
		st.insert(arr[i]);
	}
	if (*st.rbegin() - *st.begin() <= c) {
		ans.push_back(x);
	}

	while (y + 1 <= n) {
		st.erase(st.find(arr[x]));
		x++; y++;
		st.insert(arr[y]);
		if (*st.rbegin() - *st.begin() <= c) {
			ans.push_back(x);
		}
	}

	if (ans.size() > 0) {
		for (int it : ans) printf("%d\n", it);
	}
	else printf("NONE\n");
	
	return 0;
}
