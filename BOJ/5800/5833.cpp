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
#include <time.h>
#include <stdlib.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

vector<int> adj[15];
int pos[15];

int compute(int n) {
	int ret = 0;
	for (int i = 1; i <= n; i++){
		for (int nxt : adj[i]) {
			ret += abs(pos[i] - pos[nxt]);
		}
	}
	return ret;
}

int simulated_annealing(int n) {
	double t = 1;
	double dec = 0.99997;
	int e1, e2;
	int k = 300;
	int minv = INF;

	minv = e1 = compute(n);

	for (int i = 0; i < 300000; i++) {
		// 랜덤한 다음 상태 만들기
		int x = rand() % n + 1;
		int y = rand() % (n - 1) + 1;
		if (y >= x) y = y % n + 1;
		swap(pos[x], pos[y]);

		// 새로운 상태 에너지 계산
		e2 = compute(n);
		minv = min(minv, e2);

		// 새로운 상태로 이동할 것인지 체크
		double p = exp((double)(e1 - e2) / (k*t));
		if (p > (double)(rand() % 10000) / 10000) e1 = e2;
		else { swap(pos[x], pos[y]); }

		t *= dec;

		//if (i % 10000 == 0) printf("i %d / %lf\n", i, exp(-1.0 / (k*t)));
	}
	return minv;
}

int main()
{
	int n;
	
	srand(time(NULL));
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 3; j++) {
			int nxt;
			scanf("%d", &nxt);
			if (i < nxt) adj[i].push_back(nxt);
		}
	}
	
	for (int i = 1; i <= n; i++) {
		pos[i] = i;
	}
	printf("%d\n", simulated_annealing(n));
	return 0;
}
