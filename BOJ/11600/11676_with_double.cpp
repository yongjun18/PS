#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int b[1010];
vector<int> ing[100];
int incom[100][100];

int main()
{
	int r, s, m, d, n;
	ll ans;
	double ansd;

	scanf("%d %d %d %d %d", &r, &s, &m, &d, &n);
	for(int i=1; i<=r; i++){
		scanf("%d", &b[i]);
	}

	for(int i=1; i<=s+m+d; i++){
		int k;
		scanf("%d", &k);
		ing[i].resize(k);
		for(int j=0; j<k; j++){
			scanf("%d", &ing[i][j]);
		}
	}

	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		incom[x][y] = incom[y][x] = 1;
	}

	ans = ansd = 0;
	for(int ns=1; ns<=s; ns++){
		for(int nm=s+1; nm<=s+m; nm++){
			for(int nd=s+m+1; nd<=s+m+d; nd++){
				if(incom[ns][nm] || incom[nm][nd] || incom[nd][ns])
					continue;

				ll now = 1;
				double nowd = 1;
				set<int> st;

				for(int it : ing[ns]) st.insert(it);
				for(int it : ing[nm]) st.insert(it);
				for(int it : ing[nd]) st.insert(it);

				for(int it : st){
					now *= b[it];
					nowd *= b[it];
				}
				ans += now;
				ansd += nowd;
			}
		}
	}
	if(ansd > 1.1e18 || ans > (ll)1e18){
		printf("too many\n");
	}
	else printf("%lld\n", ans);
	return 0;
}
