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
	int a, b, c, d, e, f;
	int ax, ay;

	scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);

	for (int x = -1000; x <= 1000; x++){
		for (int y = -1000; y <= 1000; y++){
			if (a * x + b * y == c){
				if (d * x + e * y == f){
					ax = x;
					ay = y;
					break;
				}
			}
		}
	}
	printf("%d %d\n", ax, ay);
	return 0;
}
