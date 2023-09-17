#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

char s[55];
char t[55];
int dp[55][55][2];

int main()
{
	int slen, tlen;

	scanf("%s %s", s, t);
	slen = strlen(s);
	tlen = strlen(t);

	for (int i = 0; i + slen - 1 < tlen; i++) {
		if (strncmp(s, t + i, slen) == 0) {
			dp[i][i + slen - 1][0] = 1;
		}
	}
	reverse(s, s + slen);
	for (int i = 0; i + slen - 1 < tlen; i++) {
		if (strncmp(s, t + i, slen) == 0) {
			dp[i][i + slen - 1][1] = 1;
		}
	}

	for (int len = 1; len <= tlen; len++) {
		for (int i = 0; i + len - 1 < tlen; i++) {
			int j = i + len - 1;
			if (j + 1 < tlen) {
				if (t[j + 1] == 'A') dp[i][j + 1][0] |= dp[i][j][0];
				if (t[j + 1] == 'B') dp[i][j + 1][1] |= dp[i][j][0];
			}
			if (i - 1 >= 0) {
				if (t[i - 1] == 'A') dp[i - 1][j][1] |= dp[i][j][1];
				if (t[i - 1] == 'B') dp[i - 1][j][0] |= dp[i][j][1];
			}
		}
	}
	printf("%d\n", dp[0][tlen - 1][0]);
	return 0;
}
