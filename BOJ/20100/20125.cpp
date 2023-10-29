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

int n;
char arr[1010][1010];

int computeLen(int x, int y, int dx, int dy) {
	int ret = 0;
	
	while (1 <= x && x <= n && 1 <= y && y <= n) {
		if (arr[x][y] == '_') break;
		ret++;
		x += dx;
		y += dy;
	}
	return ret;
}

int main()
{
	int headX, headY;
	int heartX, heartY;
	int armL, armR;
	int waist;
	int waistX, waistY;
	int legL, legR;

	scanf("%d", &n);
	headX = headY = -1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf(" %c", &arr[i][j]);

			if (headX == -1 && arr[i][j] == '*') {
				headX = i;
				headY = j;
			}
		}
	}
	heartX = headX + 1;
	heartY = headY;

	armL = computeLen(heartX, heartY - 1, 0, -1);
	armR = computeLen(heartX, heartY + 1, 0, 1);

	waist = computeLen(heartX + 1, heartY, 1, 0);
	waistX = heartX + waist;
	waistY = heartY;

	legL = computeLen(waistX + 1, waistY - 1, 1, 0);
	legR = computeLen(waistX + 1, waistY + 1, 1, 0);

	printf("%d %d\n", heartX, heartY);
	printf("%d %d %d %d %d\n", armL, armR, waist, legL, legR);

	return 0;
}
