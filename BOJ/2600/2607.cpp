#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <string.h>
#include <vector>
using namespace std;

char str[110][15];

int compare(int x, int xSkip, int y, int ySkip) {
	int i = 0;
	int j = 0;
	
	while (1) {
		if (str[x][i] == '\0' && str[y][j] == '\0') {
			return 1;
		}
		if (i == xSkip) { i++; continue; }
		if (j == ySkip) { j++; continue; }

		if (str[x][i] == str[y][j]) { i++; j++; }
		else { break; }
	}
	return 0;
}

int isSimilar(int x, int y) {
	for (int xSkip = -1; xSkip == -1 || str[x][xSkip]; xSkip++) {
		for (int ySkip = -1; ySkip == -1 || str[y][ySkip]; ySkip++) {
			if (compare(x, xSkip, y, ySkip)) {
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	int n, ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int len;
		scanf("%s", str[i]);
		len = strlen(str[i]);
		sort(str[i], str[i] + len);
	}

	ans = 0;
	for (int i = 1; i < n; i++) {
		if (isSimilar(0, i)) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
