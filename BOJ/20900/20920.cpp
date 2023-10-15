#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

struct Node {
	string str;
	int cnt;
	bool operator < (const Node &rhs) const {
		if (cnt != rhs.cnt) return cnt > rhs.cnt;
		if (str.length() != rhs.str.length()) return str.length() > rhs.str.length();
		return str < rhs.str;
	}
};

char tmp[15];
vector<string> input;
vector<Node> nodes;

int main()
{
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", tmp);
		if (strlen(tmp) >= m) {
			input.push_back(tmp);
		}
	}
	sort(input.begin(), input.end());

	nodes.push_back({ input[0], 1 });
	for (int i = 1; i < input.size(); i++) {
		if (input[i - 1] == input[i]) {
			nodes.back().cnt++;
		}
		else {
			nodes.push_back({ input[i], 1 });
		}
	}
	sort(nodes.begin(), nodes.end());

	for (int i = 0; i < nodes.size(); i++) {
		printf("%s\n", nodes[i].str.c_str());
	}
	return 0;
}
