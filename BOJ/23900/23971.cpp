#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() 
{
	int h, w, n, m;
	int t1, t2;

	scanf("%d %d %d %d", &h, &w, &n, &m);
	t1 = (h + n) / (n + 1);
	t2 = (w + m) / (m + 1);

	printf("%d\n", t1 * t2);
	return 0;
}
