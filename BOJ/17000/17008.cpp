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

int n, m;
int state[1010];
int clause[10100][3];

int compute() {
	int ret = 0;
	for (int i = 0; i < m; i++) {
		int tcnt = 0;
		for (int j = 0; j < 3; j++) {
			if (clause[i][j] == state[abs(clause[i][j])]) {
				tcnt++;
			}
		}
		if (tcnt == 0) ret++;
	}
	return ret;
}

int simulated_annealing() {
	double t = 1;
	double dec = 0.999;
	int e1, e2;
	int k = 300;

	e1 = compute();
	if (e1 == 0) return 1;

	for (int l = 0; l < 5000; l++) {
		// 랜덤한 다음 상태 만들기
		vector<int> xi;
		for (int i = 0; i < m; i++) {
			int tcnt = 0;
			for (int j = 0; j < 3; j++) {
				if (clause[i][j] == state[abs(clause[i][j])]) {
					tcnt++;
				}
			}
			if (tcnt == 0) {
				for (int j = 0; j < 3; j++) {
					if (j && clause[i][j] == clause[i][j - 1]) continue;
					xi.push_back(clause[i][j]);
				}
			}
		}
		int change = abs(xi[rand() % xi.size()]);
		state[change] *= -1;

		// 새로운 상태 에너지 계산
		e2 = compute();
		if (e2 == 0) return 1;
		
		// 새로운 상태로 이동할 것인지 체크
		double p = exp((double)(e1 - e2) / (k*t));
		if (p > (double)(rand() % 10000) / 10000) e1 = e2;
		else { state[change] *= -1; }

		t *= dec;

		//if (l % 1000 == 0) printf("l %d / %lf\n", l, exp(-1.0 / (k*t)));
	}
	return 0;
}

int main()
{
	srand(time(NULL));
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &clause[i][j]);
		}
		sort(clause[i], clause[i] + 3);
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			state[abs(clause[i][j])] = clause[i][j];
		}
	}

	if (simulated_annealing()) {
		printf("1\n");
		for (int i = 1; i <= n; i++) {
			printf("%d ", (state[i] > 0));
		}
	}
	else printf("0\n");

	return 0;
}
