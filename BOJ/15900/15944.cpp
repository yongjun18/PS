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

int n, m, siz;
char arr[510][510];
int visit[510][510][110];

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int dx8[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy8[] = { -1, 0, 1, 1, -1, -1, 0, 1 };

struct Node{
	int x, y, wsum, level;
};
deque<Node> dq;

int valid(int x, int y){
	return 0 <= x && x < n && 0 <= y && y < m;
}

int main()
{
	scanf("%d %d %d", &n, &m, &siz);
	for (int i = 0; i < n; i++){
		scanf("%s", arr[i]);
	}

	dq.push_front({ 0, 0, 0, 0 });
	visit[0][0][0] = 1;

	while (dq.size()){
		int x = dq.front().x;
		int y = dq.front().y;
		int wsum = dq.front().wsum;
		int level = dq.front().level;
		dq.pop_front();

		if (x == n - 1 && y == m - 1){
			printf("%d\n", wsum);
			break;
		}

		for (int d = 0; d < 4; d++){
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (valid(nx, ny) == 0) continue;

			if (visit[nx][ny][0] == 0 && arr[nx][ny] == '.'){
				dq.push_front({ nx, ny, wsum, 0 });
				visit[nx][ny][0] = 1;
			}
			if (visit[nx][ny][1] == 0 && arr[nx][ny] == '#'){
				dq.push_back({ nx, ny, wsum + 1, 1 });
				visit[nx][ny][1] = 1;
			}
		}
		for (int d = 0; d < 8; d++){
			int nx = x + dx8[d];
			int ny = y + dy8[d];
			if (valid(nx, ny) == 0) continue;

			if (0 < level && level < siz && visit[nx][ny][level + 1] == 0){
				dq.push_front({ nx, ny, wsum, level + 1 });
				visit[nx][ny][level + 1] = 1;
			}
		}
	}
	return 0;
}
