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

char name[510][25];
double leg1[510];
double leg2[510];

struct Node{
	int idx;
	bool operator < (const Node& rhs) const{
		return leg2[idx] < leg2[rhs.idx];
	}
};

vector<Node> vec;

int main()
{
	int n;
	double ans;
	int ansr[4];

	scanf("%d", &n);

	for (int i = 0; i < n; i++){
		scanf("%s %lf %lf", name[i], &leg1[i], &leg2[i]);
	}
	

	ans = INF;
	for (int i = 0; i < n; i++){
		double now = leg1[i];

		vec.clear();
		for (int j = 0; j < n; j++){
			if (i == j) continue;
			vec.push_back({ j });
		}
		sort(vec.begin(), vec.end());

		for (int j = 0; j < 3; j++){
			now += leg2[vec[j].idx];
		}
		if (ans > now){
			ans = now;
			ansr[0] = i;
			for (int j = 0; j < 3; j++){
				ansr[j + 1] = vec[j].idx;
			}
		}
	}

	printf("%lf\n", ans);
	for (int it : ansr){
		printf("%s\n", name[it]);
	}
	return 0;
}
