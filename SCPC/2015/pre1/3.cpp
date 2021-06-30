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

vector<int> divv, divv2;

void get_divv(int x, vector<int>& res){
	int sqrtv = sqrt(x) + 5;
	for (int i = 1; i <= sqrtv; i++){
		if (x % i == 0){
			res.push_back(i);
			res.push_back(x / i);
		}
	}
}

int check(int b, int bsum){
	while (bsum > 0){
		if (bsum % b != 1){
			return 0;
		}
		bsum /= b;
	}
	return 1;
}

int main()
{
	int t;
	
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		int ans;

		scanf("%d", &n);
		ans = n + 1;

		divv.clear();
		divv2.clear();
		get_divv(n, divv);

		for (int it : divv){
			int k = it;
			int bsum = n / k;
			get_divv(bsum - 1, divv2);

			for (int it2 : divv2){
				if (it2 <= k) continue;
				if (check(it2, bsum)){
					ans = min(ans, it2);
				}
			}
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
