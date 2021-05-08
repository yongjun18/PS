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

int n;
long double p, s, v;

long double solve(long double c){
	long double alg = n * pow(log2((long double)n), c * sqrt((long double)2)) / (p * 1e9);
	long double tour = s * (1 + 1 / c) / v;
	return alg + tour;
}
long double ternary_search(long double x, long double y){
	long double lo = x;
	long double hi = y;
	for (int i = 0; i < 300; i++) {
		long double m1 = (2 * lo + hi) / 3;
		long double m2 = (lo + 2 * hi) / 3;

		if (solve(m1) <= solve(m2)) hi = m2;
		else lo = m1;
	}
	return lo;
}


int main()
{ 
	long double c;
	scanf("%d %Lf %Lf %Lf", &n, &p, &s, &v);
	
	c = ternary_search(0, 1e9);
	printf("%.9Lf %.9Lf\n", solve(c), c);
	return 0;
}
