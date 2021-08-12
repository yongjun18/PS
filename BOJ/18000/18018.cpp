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

char pstr[25];
int plen;

int n;
char str[100100][25];
int len[100100];
int start[26];

int eliminate(){
	for (int i = 0; i < n; i++){
		if (str[i][0] != pstr[plen - 1]) continue;

		int other = start[str[i][len[i] - 1] - 'a'];
		if (str[i][0] == str[i][len[i] - 1]) other--;

		if (other == 0){
			printf("%s!\n", str[i]);
			return 1;
		}
	}
	return 0;
}

int keep(){
	for (int i = 0; i < n; i++){
		if (str[i][0] != pstr[plen - 1]) continue;

		printf("%s\n", str[i]);
		return 1;
	}
	return 0;
}

int main()
{
	scanf("%s", pstr);
	plen = strlen(pstr);

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%s", str[i]);
		len[i] = strlen(str[i]);
		start[str[i][0] - 'a']++;
	}

	if (eliminate() == 0){
		if (keep() == 0){
			printf("?\n");
		}
	}
	return 0;
}
