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

struct vec {
	double x, y;
	explicit vec(double x, double y) { this->x = x; this->y = y; }
	vec() { x = 0; y = 0; }

	bool operator == (const vec& rhs) { return x == rhs.x && y == rhs.y; }
	bool operator < (const vec& rhs) { if (x != rhs.x) return x < rhs.x; return y < rhs.y; }
	vec operator + (const vec& rhs) { return vec(x + rhs.x, y + rhs.y); }
	vec operator - (const vec& rhs) { return vec(x - rhs.x, y - rhs.y); }
	vec operator * (double rhs) const { return vec(x * rhs, y * rhs); }
	double cross(const vec& rhs) const { return x * rhs.y - rhs.x * y; }
};

double ccw(vec a, vec b) {
	return a.cross(b);
}
double ccw(vec p, vec a, vec b) {
	return ccw(a - p, b - p);
}

// 교차점이 필요없는 경우 두 선분의 접촉(교차 + 끝점이 스치듯 만남) 여부 확인
bool segment_intersection(vec a, vec b, vec c, vec d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

const int S = 25;
int n, m, l;
vector< pair<int, int> > edges;
vector<vec> p;

vector<int> now;

// 교점 수 세는 함수
int compute() {
	int ret = 0;
	
	for (int i = 0; i < edges.size(); i++) {
		for (int j = i + 1; j < edges.size(); j++) {
			int from1 = edges[i].first;
			int to1 = edges[i].second;
			int from2 = edges[j].first;
			int to2 = edges[j].second;

			if (from1 == from2 || from1 == to2 || to1 == from2 || to1 == to2)
				continue;

			if (segment_intersection(
				p[now[from1]], p[now[to1]], 
				p[now[from2]], p[now[to2]]))
				ret++;
		}
	}
	return ret;
}

int minv;
vector<int> ans;

// 담금질 기법
void simulated_annealing() {
	double t = 1;
	double dec = 0.9995;
	int e1, e2;
	int k = 300;

	// 초기 상태
	for (int i = 0; i <= l; i++) {
		now.push_back(i);
	}
	ans = now;
	minv = e1 = compute();

	for (int i = 0; i < 20000; i++) {
		// 새로운 상태 랜덤하게 생성 후 에너지 계산
		int x = rand() % n + 1;
		int y = rand() % l + 1;
		if (x == y) continue;
		swap(now[x], now[y]);
		e2 = compute();

		double p = exp((double)(e1 - e2) / (k*t));
		// 상태 변경 성공
		if (p > (double)(rand() % 10000) / 10000) e1 = e2;
		// 이전 상태로 되돌림
		else swap(now[x], now[y]);

		if (minv > e1) {
			minv = e1;
			ans = now;
		}
		t *= dec;

		// 에너지가 1증가 했을 때, 상태를 바꿀 확률을 체크하며 
		// 적당한 k값과 온도 감률을 찾는다.
		// 후반에는 에너지가 증가하지 않도록 하여, local minima를 찾자.
		if (i % 100 == 0) {
			printf("i %d\n", i);
			printf("probability %lf\n", exp(-1.0 / (k*t)));
			printf("current minv %d / e1 %d\n", minv, e1);
			printf("\n");
		}
	}
}

int main()
{
	srand(time(NULL));
	freopen("01.txt", "r", stdin);
	
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		edges.push_back({ x, y });
	}
	scanf("%d", &l);
	p.resize(l + 1);
	for (int i = 1; i <= l; i++) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	fclose(stdin);

	simulated_annealing();

	if (minv <= S) {
		printf("success!\n");
		freopen("output.txt", "w", stdout);
		for (int i = 1; i <= n; i++) {
			printf("%d\n", ans[i]);
		}
		fclose(stdout);
	}
	else printf("fail\n");
	
	return 0;
}
