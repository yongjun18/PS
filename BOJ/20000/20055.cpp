#include <stdio.h>
#include <algorithm>
#include <vector>
#include <memory.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <string>
#include <math.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int n, k;
int robot[205];
int durability[205];

void rotate() {
	for (int i = 2 * n - 1; i >= 0; i--) {
		robot[i + 1] = robot[i];
		durability[i + 1] = durability[i];
	}
	durability[0] = durability[2 * n];
	robot[n] = 0;
	robot[0] = 0;
}

void move() {
	robot[n - 1] = 0;
	for (int i = n - 2; i >= 0; i--) {
		if (robot[i] == 1 && durability[i + 1] > 0 && robot[i + 1] == 0) {
			robot[i] = 0;
			robot[i + 1] = 1;
			durability[i + 1]--;
		}
	}
}

void upload() {
	if (durability[0] > 0) {
		robot[0] = 1;
		durability[0]--;
	}
}

int check() {
	int cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (durability[i] == 0) {
			cnt++;
		}
	}
	return cnt;
}

int main()
{
	int stage;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < 2 * n; i++) {
		scanf("%d", &durability[i]);
	}

	stage = 0;
	while (true) {
		stage++;
		rotate();
		move();
		upload();
		if (check() >= k) {
			printf("%d\n", stage);
			break;
		}
	}
	return 0;
}
