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

char str[1000100];
int to[1000100];
vector< pair<char,int> > st;

int is_open(char c){
	if (c == '(') return 1;
	if (c == '{') return 1;
	if (c == '[') return 1;
	return 0;
}
int is_matched(char o, char c){
	if (o == '(' && c == ')') return 1;
	if (o == '{' && c == '}') return 1;
	if (o == '[' && c == ']') return 1;
	return 0;
}

int main()
{
	int t;
	
	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int len, ans;
		int x, y;

		scanf("%s", str);
		len = strlen(str);
		st.clear();
		for (int i = 0; i < len + 5; i++){
			to[i] = -1;
		}

		for (int i = 0; i < len; i++){
			if (is_open(str[i])){
				st.push_back({ str[i], i });
			}
			else{
				if (st.size() > 0 && is_matched(st.back().first, str[i])){
					to[st.back().second] = i;
					st.pop_back();
				}
				else{
					st.clear();
				}
			}
		}

		ans = 0;
		x = 0;
		while (x < len){
			if (to[x] != -1){
				y = to[x];
				while (to[y + 1] != -1) y = to[y + 1];
				ans = max(ans, y - x + 1);
				x = y + 1;
			}
			else{
				x++;
			}
		}
		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
