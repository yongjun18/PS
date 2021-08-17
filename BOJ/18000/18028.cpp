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

int arr[105];
int fills[105];

vector< pair<int, int> > vec;

int main()
{
	int n, m, s, d;
	int news, sum;

	scanf("%d %d %d %d", &n, &m, &s, &d);
	for (int i = 0; i < s; i++){
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < s; i++){
		vec.push_back({ arr[i], i });
	}
	sort(vec.begin(), vec.end());

	news = n;
	for (auto it : vec){
		int idx = it.second;
		int now = min(news, d - arr[idx]);
		news -= now;
		fills[idx] = now;
	}

	sum = 0;
	for (int i = 0; i < s; i++){
		if (fills[i] == 0){
			sum += arr[i];
		}
	}

	if (news > 0 || sum < m){
		printf("impossible\n");
	}
	else{
		for (int i = 0; i < s; i++){
			printf("%d ", fills[i]);
		}
		printf("\n");
	}
	return 0;
}
