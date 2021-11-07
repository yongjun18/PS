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
stack< pair<int, int> > st;
int nge[1000100];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		nge[i] = -1;
	}

	for (int i = 1; i <= n; i++) {
		while (st.size() > 0 && st.top().first < arr[i]) {
			int top = st.top().second;
			st.pop();
			nge[top] = arr[i];
		}
		st.push({ arr[i], i });
	}

	for (int i = 1; i <= n; i++) {
		printf("%d ", nge[i]);
	}
	printf("\n");
	return 0;
}
