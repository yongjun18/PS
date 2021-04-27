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

int len, n;
char str[105];

int visit[55];
int ans[105];
int succ = 0;

int val(int x, int y){
	if (x == y) return str[x] - '0';
	if (x + 1 == y) return (str[x] - '0') * 10 + (str[y] - '0');
	return -1;
}

void dfs(int now){
	if (now >= len){
		for (int i = 0; i < len;){
			if (ans[i] == 1){
				printf("%c ", str[i]);
				i++;
			}
			else{
				printf("%c%c ", str[i], str[i + 1]);
				i += 2;
			}
		}
		printf("\n");
		succ = 1;
		return;
	}

	if (str[now] == '0') return;
	
	if (succ == 0 && val(now, now) <= n && visit[val(now, now)] == 0){
		ans[now] = 1;
		visit[val(now, now)] = 1;
		dfs(now + 1);
		visit[val(now, now)] = 0;
	}
	if (succ == 0 && now + 1 < len && val(now, now + 1) <= n && visit[val(now, now + 1)] == 0){
		ans[now] = 2;
		visit[val(now, now + 1)] = 1;
		dfs(now + 2);
		visit[val(now, now + 1)] = 0;
	}
}

int main()
{
	int tmp;

	scanf("%s", str); 
	len = strlen(str);
	tmp = len;
	
	n = 0;
	while (tmp > 0){
		n++;
		if (n >= 10) tmp -= 2;
		else tmp -= 1;
	}
	dfs(0);
	return 0;
}
