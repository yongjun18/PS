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


int main()
{
	int ga1, gb1, ga2, gb2;
	int ea1, eb1, ea2, eb2;
	int gwin;

	scanf("%d %d %d %d", &ga1, &gb1, &ga2, &gb2);
	scanf("%d %d %d %d", &ea1, &eb1, &ea2, &eb2);

	gwin = 0;

	for (int g1 = ga1; g1 <= gb1; g1++) {
		for (int g2 = ga2; g2 <= gb2; g2++) {
			for (int e1 = ea1; e1 <= eb1; e1++) {
				for (int e2 = ea2; e2 <= eb2; e2++) {
					
					if (g1 + g2 > e1 + e2) gwin++;
					if (g1 + g2 < e1 + e2) gwin--;
				}
			}
		}
	}

	if (gwin > 0) printf("Gunnar\n");
	if (gwin < 0) printf("Emma\n");
	if (gwin == 0) printf("Tie\n");

	return 0;
}
