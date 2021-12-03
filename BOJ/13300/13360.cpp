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

char str[10100];

int how_many(int rank) {
	if (21 <= rank && rank <= 25) return 2;
	if (16 <= rank && rank <= 20) return 3;
	if (11 <= rank && rank <= 15) return 4;
	if (1 <= rank && rank <= 10) return 5;
	return -1;
}

int main()
{
	int rank = 25;
	int star = 0;
	int streak = 0;
	int need;

	scanf("%s", str);

	for (int i = 0; str[i]; i++) {
		if (rank == 0) continue;

		if (str[i] == 'W') {
			streak++;
			star++;
			if (rank >= 6 && streak >= 3) star++;

			need = how_many(rank);
			if (star > need) {
				star -= need;
				rank--;
			}
		}

		if (str[i] == 'L') {
			streak = 0;

			if (rank <= 20) {
				star--;
				if (star < 0) {
					if (rank == 20) star = 0;
					else {
						rank++;
						star += how_many(rank);
					}
				}
			}
		}
	}

	if (rank == 0) printf("Legend\n");
	else printf("%d\n", rank);
	return 0;
}
