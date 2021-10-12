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

struct Node {
	int b, p, q, r;
	int mul, sum;
	bool operator < (const Node& rhs) const {
		if (mul != rhs.mul) return mul < rhs.mul;
		if (sum != rhs.sum) return sum < rhs.sum;
		return b < rhs.b;
	}
};

vector<Node> vec;

int main()
{
	int n;

	scanf("%d", &n);
	vec = vector<Node>(n);
	
	for (Node& it : vec) {
		scanf("%d %d %d %d", &it.b, &it.p, &it.q, &it.r);
		it.mul = it.p * it.q * it.r;
		it.sum = it.p + it.q + it.r;
	}
	sort(vec.begin(), vec.end());

	for (int i = 0; i < 3; i++) {
		printf("%d ", vec[i].b);
	}
	printf("\n");

	return 0;
}
