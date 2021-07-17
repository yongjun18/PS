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

vector<int> vec;

int main()
{
	int x, n;
	int lo, hi;
	int ok;

	while (scanf("%d %d", &x, &n) > 0){
		x *= (int)1e7;
		vec.clear();
		for (int i = 0; i < n; i++){
			int tmp;
			scanf("%d", &tmp);
			vec.push_back(tmp);
		}
		sort(vec.begin(), vec.end());

		ok = 0;
		lo = 0;
		hi = n - 1;
		while (lo < hi){
			if (vec[lo] + vec[hi] == x){
				ok = 1;
				printf("yes %d %d\n", vec[lo], vec[hi]);
				break;
			}
			if (vec[lo] + vec[hi] < x) lo++;
			else hi--;
		}
		if (ok == 0){
			printf("danger\n");
		}
	}

	return 0;
}
