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

struct Rect{
	int x1, y1, x2, y2;
	bool operator <(const Rect& rhs) const{
		if (x1 != rhs.x1) return x1 > rhs.x1;
		if (y1 != rhs.y1) return y1 > rhs.y1;
		if (x2 != rhs.x2) return x2 < rhs.x2;
		return y2 < rhs.y2;
	}
};

vector<Rect> rects;
int dp[5010];

int inc(Rect outr, Rect inr){
	return outr.x1 <= inr.x1 && inr.x2 <= outr.x2 &&
		outr.y1 <= inr.y1 && inr.y2 <= outr.y2;
}

int main()
{
	int t;

	scanf("%d", &t); 

	for (int test = 1; test <= t; test++){
		int n, m, k;
		int maxv;
		
		scanf("%d %d %d", &n, &m, &k);

		rects.clear();
		for (int i = 0; i < k; i++){
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			rects.push_back({ x1, y1, x2, y2 });
		}
		sort(rects.begin(), rects.end());

		for (int i = 0; i < k; i++){
			dp[i] = 1;
			for (int j = 0; j < i; j++){
				if (inc(rects[i], rects[j])){
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		
		maxv = 0;
		for (int i = 0; i < k; i++){
			maxv = max(maxv, dp[i]);
		}

		printf("Case #%d\n", test);
		printf("%d\n", maxv);
	}

	return 0;
}
