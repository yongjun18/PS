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

char str[50010][210];

map<string, int> mp;
int handle(char *s, char *t){
	string tmp;
	while (s != t){
		tmp.push_back(*s);
		s++;
	}
	if (mp.find(tmp) == mp.end()){
		mp[tmp] = mp.size();
	}
	return mp[tmp];
}
char* hend(char *s, int is_author){
	while (1){
		if (*s == '\0') break;
		if (*s == ' ') break;
		if (*s == ':' && is_author) break;
		if (*s == '\n') break;
		s++;
	}
	return s;
}

int recent[3500100];
int dp[50010];
int pv[50010];

vector<int> alist;

int main()
{
	int n;
	int ans, alast;

	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++){
		fgets(str[i], 200, stdin);
	}

	for (int i = 1; i <= n; i++){
		char *s, *t;

		s = &str[i][1];
		t = hend(s, 1);
		int spk = handle(s, t);
		s = t;

		int maxv = 0;
		int maxp = 0;
		while (*s != '\0'){
			if (*s == ' ' && *(s + 1) == '@'){
				s = s + 2;
				t = hend(s, 0);
				int oth = handle(s, t);
				if (spk != oth && recent[oth] != 0){
					if (maxv < dp[recent[oth]]){
						maxv = dp[recent[oth]];
						maxp = recent[oth];
					}
				}
				s = t;
			}
			else s++;
		}
		dp[i] = maxv + 1;
		pv[i] = maxp;

		if (dp[recent[spk]] < dp[i]){
			recent[spk] = i;
		}
	}

	ans = 0;
	alast = 0;
	for (int i = 1; i <= n; i++){
		if (ans < dp[i]){
			ans = dp[i];
			alast = i;
		}
	}
	while (alast > 0){
		alist.push_back(alast);
		alast = pv[alast];
	}
	printf("%d\n", ans);
	for (int i = ans - 1; i >= 0; i--){
		printf("%d ", alist[i]);
	}
	printf("\n");
	return 0;
}
