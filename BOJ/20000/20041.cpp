#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int sx, sy;
vector< pair<int,int> > pol;

int possible(){
	int ok = 1;
	for(auto it : pol){
		int dx = abs(sx - it.first);
		int dy = abs(sy - it.second);
		if(it.first >= sx && dx >= dy) ok = 0;
	}
	if(ok) return 1;

	ok = 1;
	for(auto it : pol){
		int dx = abs(sx - it.first);
		int dy = abs(sy - it.second);
		if(it.second <= sy && dx <= dy) ok = 0;
	}
	if(ok) return 1;

	return 0;
}

int main()
{
	int n;
	int res;

	scanf("%d", &n);
	pol.resize(n);
	for(int i=0; i<n; i++){
		scanf("%d %d", &pol[i].first, &pol[i].second);
	}
	scanf("%d %d", &sx, &sy);

	res = 0;
	res += possible();
	for(auto &it : pol) swap(it.first, it.second);
	swap(sx, sy);
	res += possible();

	if(res > 0) printf("YES\n");
	else printf("NO\n");
	return 0;
}
