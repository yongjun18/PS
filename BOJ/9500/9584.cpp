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

char scn[20];
char input[20];

vector<string> ans;

int main()
{
	int n;

	scanf("%s", scn);
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		int ok = 1;
		scanf("%s", input);
		for (int j = 0; scn[j]; j++){
			if (scn[j] != '*' && scn[j] != input[j]){
				ok = 0;
				break;
			}
		}
		if (ok){
			ans.push_back(input);
		}
	}
	printf("%d\n", ans.size());
	for (auto it : ans){
		printf("%s\n", it.c_str());
	}
	return 0;
}
