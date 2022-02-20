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

int arr[300100];
double prob[1000100];

int main()
{
	int n;
	int mx;
	double ans;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	mx = arr[0];
	for (int i = 0; i < mx; i++) {
		prob[i] = 1.0 / mx;
	}

	for (int i = 1; i < n; i++) {
		for (int j = arr[i]; j < mx; j++) {
			prob[j % arr[i]] += prob[j];
		}
		mx = min(mx, arr[i]);
	}

	ans = 0.0;
	for (int i = 0; i < mx; i++) {
		ans += prob[i] * i;
	}
	printf("%.12lf\n", ans);
	return 0;
}
