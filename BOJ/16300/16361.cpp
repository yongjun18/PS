#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

vector< pair<int, int> > dot;

int solve(double x){
	int now = 0;
	int minv, maxv;
	
	if (dot[0].first == 0 && dot[0].second > x) 
		return 0;

	while (now < dot.size()){
		if (dot[now].second > x) break;
		now++;
	}

	minv = INF;
	maxv = 0;
	for (int i = now; i < dot.size(); i++){
		minv = min(minv, dot[i].second);
		maxv = max(maxv, dot[i].second);
	}

	while (now < dot.size()){
		if (dot[now].second > minv + 2 * x) break;
		now++;
	}

	while (now < dot.size()){
		if (dot[now].second < maxv - 2 * x) break;
		now++;
	}

	if (now == dot.size()) return 1;
	return 0;
}

double parametric_search(double x, double y){
	for (int i = 0; i < 60; i++){
		double mid = (x + y) / 2;
		if (solve(mid)) y = mid;
		else x = mid;
	}
	return y;
}

int main()
{
	int n;

	scanf("%d", &n);
	dot.resize(n);
	for (int i = 0; i < n; i++){
		scanf("%d %d", &dot[i].first, &dot[i].second);
	}
	sort(dot.begin(), dot.end());

	printf("%.1lf\n", parametric_search(0, 1e9));
	return 0;
}
