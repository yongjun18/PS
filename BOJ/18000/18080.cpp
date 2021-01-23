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
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int score[300100];
int cnt[1000100];
int up[1000100];
int visit[1000100];
double lazy[1000100];
double avg[300100];

int main()
{
	int n, w;

	scanf("%d %d", &n, &w);
	for (int i = 1; i <= n; i++){
		avg[i] = 1;
		score[i] = 0;
	}
	cnt[0] = n;

	for (int i = 1; i <= w; i++){
		int k;
		vector<int> now;
		scanf("%d", &k);
		now.resize(k);
		for (int j = 0; j < k; j++){
			scanf("%d", &now[j]);
		}

		for (int it : now){
			avg[it] += lazy[score[it]];
			cnt[score[it]]--;
			up[score[it]]++;
		}

		for (int it : now){
			avg[it] -= (double)cnt[score[it] + 1] / w * (w - i + 1);
		}

		for (int it : now){
			if (visit[score[it]] == i) continue;
			visit[score[it]] = i;
			lazy[score[it]] += (double)up[score[it]] / w * (w - i + 1);
		}

		for (int it : now){
			up[score[it]] = 0;
			score[it]++;
			cnt[score[it]]++;
			avg[it] -= lazy[score[it]];
		}
	}
	for (int i = 1; i <= n; i++){
		avg[i] += lazy[score[i]];
		printf("%.9lf\n", avg[i]);
	}
	return 0;
}
