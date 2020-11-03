#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

deque< pair<int,int> > deq;
int visit[200100];

int main()
{
	int n, k;

	scanf("%d %d", &n, &k);

	visit[n] = 1;
	deq.push_front(make_pair(n, 0));

	while (deq.size()){
		int pos = deq.front().first;
		int tim = deq.front().second;
		deq.pop_front();

		if (pos == k){
			printf("%d\n", tim);
			break;
		}

		if (pos < k && visit[2 * pos] == 0){
			visit[2 * pos] = 1;
			deq.push_front(make_pair(2 * pos, tim));
		}
		if (pos + 1 <= k && visit[pos + 1] == 0){
			visit[pos + 1] = 1;
			deq.push_back(make_pair(pos + 1, tim + 1));
		}
		if (pos - 1 >= 0 && visit[pos - 1] == 0){
			visit[pos - 1] = 1;
			deq.push_back(make_pair(pos - 1, tim + 1));
		}
	}
	return 0;
}
