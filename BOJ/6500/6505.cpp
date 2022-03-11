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
#include <functional>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 85;
int p[MX];
char str[MX];
vector<int> sparse[31];
vector<int> res;
char ans[MX];

vector<int> operation(const vector<int>& vec1, const vector<int>& vec2) {
	int siz = vec1.size();
	vector<int> ret(siz);
	for (int i = 1; i < siz; i++) {
		ret[i] = vec1[vec2[i]];
	}
	return ret;
}

int main() {
	int n, m;

	while (1) {
		scanf("%d %d", &n, &m);
		if (n == 0) break;

		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
		}
		fgets(str + 1, MX - 1, stdin);
		fgets(str + 1, MX - 1, stdin);

		sparse[0].resize(n + 1);
		for (int i = 1; i <= n; i++) {
			sparse[0][i] = p[i];
		}
		for (int i = 1; (1 << i) <= m; i++) {
			sparse[i] = operation(sparse[i - 1], sparse[i - 1]);
		}

		res.resize(n + 1);
		for (int i = 1; i <= n; i++) {
			res[i] = i;
		}

		for (int i = 0; (1 << i) <= m; i++) {
			if ((1 << i) & m) {
				res = operation(res, sparse[i]);
			}
		}

		for (int i = 1; i <= n; i++) {
			ans[res[i]] = str[i];
		}
		ans[n + 1] = '\0';
		printf("%s\n", ans + 1);
	}
	return 0;
}
