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

struct Grad{
	int gi, ai, bi;
	int idx;
	bool operator<(const Grad& rhs) const{
		return (double)ai / bi > (double)rhs.ai / rhs.bi;
	}
};

vector<Grad> grads;
double ans[100100];

int main()
{
	int n, a, b;
	double tota, totb;

	scanf("%d %d %d", &n, &a, &b);
	for (int i = 0; i < n; i++){
		int gi, ai, bi;
		scanf("%d %d %d", &gi, &ai, &bi);
		grads.push_back({ gi, ai, bi, i });
	}
	sort(grads.begin(), grads.end());

	tota = totb = 0;
	for (int i = 0; i < n; i++){
		double nowg;
		if (grads[i].bi == 0) {
			nowg = grads[i].gi;
		}
		else{
			nowg = (double)(b - totb) / grads[i].bi;
			nowg = min((double)grads[i].gi, nowg);
		}
		tota += grads[i].ai * nowg;
		totb += grads[i].bi * nowg;
		ans[grads[i].idx] = nowg;
	}

	if (tota >= a){
		printf("%.9lf %.9lf\n", tota, totb);
		for (int i = 0; i < n; i++){
			printf("%.9lf ", ans[i]);
		}
		printf("\n");
	}
	else{
		printf("-1 -1\n");
	}

	return 0;
}
