#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Shield{
	int l, u;
	double f;
	bool operator < (const Shield& rhs) const{
		return l < rhs.l;
	}
};
vector<Shield> shd;

int main()
{
	int x, y, n;
	double sum;

	scanf("%d %d %d", &x, &y, &n);
	shd.resize(n);

	for(int i=0; i<n; i++)
		scanf("%d %d %lf", &shd[i].l, &shd[i].u, &shd[i].f);
	sort(shd.begin(), shd.end());

	sum = 0;
	if(n > 0){
		for(int i=0; i<n; i++)
			sum += shd[i].f * (shd[i].u - shd[i].l);
		for(int i=0; i<n-1; i++)
			sum += shd[i+1].l - shd[i].u;
		sum += shd[0].l;
		sum += y - shd[n-1].u;
	}
	else sum = y;

	printf("%.12lf\n", x / sum);
	return 0;
}
