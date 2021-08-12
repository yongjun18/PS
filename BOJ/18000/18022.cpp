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

const int MX = 105;

char buf[MX];
char name[MX][MX];
vector<int> team[2];
int sel[MX];

int main()
{
	int n, cnt;
	int now, tnum;
	
	fgets(buf, MX, stdin);
	cnt = 0;
	for (int i = 0; buf[i]; i++){
		if (buf[i] == ' ') cnt++;
	}
	cnt++;

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", name[i]);
	}

	now = -1;
	tnum = 0;
	for (int i = 0; i < n; i++){
		int nowcnt = 0;
		while (1){
			now = (now + 1) % n;
			if (sel[now] == 0){
				nowcnt++;
			}
			if (nowcnt >= cnt){
				sel[now] = 1;
				team[tnum].push_back(now);
				tnum ^= 1;
				break;
			}
		}
	}

	printf("%d\n", team[0].size());
	for (int it : team[0]){
		printf("%s\n", name[it]);
	}
	printf("%d\n", team[1].size());
	for (int it : team[1]){
		printf("%s\n", name[it]);
	}

	return 0;
}
