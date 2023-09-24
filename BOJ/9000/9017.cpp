#include <stdio.h>
#include <algorithm>
#include <memory.h>
#include <string.h>
#include <vector>
using namespace std;

int arr[1010];
int cnt[210];
int tmpcnt[210];
int score[210];
int fifth[210];

struct Team {
	int score, fifth, num;
	bool operator < (const Team &rhs) const {
		if (score != rhs.score) return score < rhs.score;
		return fifth < rhs.fifth;
	}
};

vector<Team> teams;

int main()
{
	int t;

	scanf("%d", &t);
	while (t--) {
		int n, now;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &arr[i]);
		}
		memset(cnt, 0, sizeof(cnt));
		memset(tmpcnt, 0, sizeof(tmpcnt));
		memset(score, 0, sizeof(score));
		memset(fifth, 0, sizeof(fifth));
		teams.clear();

		for (int i = 0; i < n; i++) {
			cnt[arr[i]]++;
		}
		
		now = 1;
		for (int i = 0; i < n; i++) {
			if (cnt[arr[i]] >= 6) {
				tmpcnt[arr[i]]++;
				if (tmpcnt[arr[i]] <= 4) {
					score[arr[i]] += now;
				}
				if (tmpcnt[arr[i]] == 5) {
					fifth[arr[i]] = now;
				}
				now++;
			}
		}
		
		for (int i = 1; i <= 200; i++) {
			if (cnt[i] >= 6) {
				teams.push_back({ score[i], fifth[i], i });
			}
		}
		sort(teams.begin(), teams.end());

		printf("%d\n", teams[0].num);
	}
	return 0;
}
