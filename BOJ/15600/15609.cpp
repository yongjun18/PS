#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int r[4100];
double pnow[4100];
double pnxt[4100];

vector< pair<int,int> > now, nxt;

void mergee(int x1, int y1, int x2, int y2){
	for(int i=x1; i<=y1; i++){
		for(int j=x2; j<=y2; j++){
			pnxt[i] += pnow[i] * pnow[j] * r[i] / (r[i] + r[j]);
		}
	}
	for(int i=x2; i<=y2; i++){
		for(int j=x1; j<=y1; j++){
			pnxt[i] += pnow[i] * pnow[j] * r[i] / (r[i] + r[j]);
		}
	}
	for(int i=x1; i<=y1; i++){
		pnow[i] = pnxt[i];
		pnxt[i] = 0;
	}
	for(int i=x2; i<=y2; i++){
		pnow[i] = pnxt[i];
		pnxt[i] = 0;
	}
}

int main()
{
	int n, powv;

	scanf("%d", &n);
	for(int i=0; i<n; i++)
		scanf("%d", &r[i]);
	sort(r+1, r+n);

	powv = 2;
	while(powv*2 <= n) powv *= 2;

	for(int i=0; i<n; i++)
		pnow[i] = 1;

	for(int i=0; i<n; i++){
		if(i < n - (n-powv)*2){
			now.push_back({i, i});
		}
		else if((n-i) % 2 == 0){
			mergee(i, i, i+1, i+1);
			now.push_back({i, i+1});
		}
	}

	while(now.size() > 1){
		for(int i=0; i<now.size(); i+=2){
			int x1 = now[i].first;
			int y1 = now[i].second;
			int x2 = now[i+1].first;
			int y2 = now[i+1].second;

			mergee(x1, y1, x2, y2);
			nxt.push_back({x1, y2});
		}
		swap(now, nxt);
		nxt.clear();
	}
	printf("%.9lf\n", pnow[0]);
	return 0;
}
