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

int a[105];
char str[255];
int dat[1010][1010];
vector<int> user[1010];
vector<int> ans;

int main()
{
	int m, f, n, q;

	scanf("%d %d", &m, &f);
	for (int i = 0; i < f; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", str);
		for (int j = 0; str[j]; j++){
			int v;
			if ('0' <= str[j] && str[j] <= '9') v = str[j] - '0';
			else v = str[j] - 'a' + 10;
			for (int k = 0; k < 4; k++){
				if (v % 2 == 1){
					int bit = j * 4 + k;
					dat[i][bit] = 1;
				}
				v /= 2;
			}
		}
	}
	scanf("%d", &q);
	for (int i = 0; i < q; i++){
		ll u;
		scanf("%lld", &u);
		for (int j = 0; j < f; j++){
			user[i].push_back(u * a[j] % m);
		}
		sort(user[i].begin(), user[i].end());
		user[i].erase(unique(user[i].begin(), user[i].end()), user[i].end());
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < q; j++){
			int ok = 1;
			for (int it : user[j]){
				if (dat[i][it] == 0){
					ok = 0;
					break;
				}
			}
			if (ok == 1){
				ans.push_back(i);
				break;
			}
		}
	}
	printf("%d ", ans.size());
	for (int it : ans) printf("%d ", it);
	printf("\n");
	return 0;
}
