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

char str[1010];
char* key = "aeiou";

struct Node{
	int x, y;
	Node(){}
	Node(int _x, int _y){ x = _x; y = _y; }
	bool operator < (const Node &rhs) const{
		if (y - x != rhs.y - rhs.x) return y - x < rhs.y - rhs.x;
		else return x < rhs.x;
	}
};

int main()
{
	int t;

	scanf("%d", &t);

	for (int test = 1; test <= t; test++){
		int n;
		Node ans(INF, 2 * INF);
		
		scanf("%d", &n);
		scanf("%s", str);
		for (int i = 0; i < n; i++){
			if (str[i] == 'a'){
				int st = 1;
				for (int j = i + 1; j < n; j++){
					if (str[j] == key[st]){
						st++;
					}
					if (st == 5){
						ans = min(ans, Node(i + 1, j + 1));
						break;
					}
				}
			}
		}
		if (ans.x >= INF){
			ans.x = -1;
			ans.y = -1;
		}
		printf("Case #%d\n", test);
		printf("%d %d\n", ans.x, ans.y);
	}

	return 0;
}
