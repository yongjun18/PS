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

int arr[1010][1010];
int visit[1010][1010];

const int U = 0;
const int D = 1;
const int L = 2;
const int R = 3;
const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

int valid(int n, int x, int y){
	if (x < 0 || y < 0 || x >= n || y >= n) return 0;
	return 1;
}
int next_dir(int dir, int x, int y){
	if (arr[x][y] == 0) return dir;

	if (arr[x][y] == 1){
		if (dir == U) return R;
		if (dir == D) return L;
		if (dir == L) return D;
		if (dir == R) return U;
	}
	if (arr[x][y] == 2){
		if (dir == U) return L;
		if (dir == D) return R;
		if (dir == L) return U;
		if (dir == R) return D;
	}
	return -1;
}

int main()
{
	int t;

	scanf("%d", &t);
	
	for (int test = 1; test <= t; test++){
		int n;
		int x, y;
		int dir;
		int ans;
		
		scanf("%d", &n);
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%1d", &arr[i][j]);
				visit[i][j] = 0;
			}
		}

		dir = R;
		x = y = 0;
		while (valid(n, x, y)){
			visit[x][y] = 1;
			dir = next_dir(dir, x, y);
			x += dx[dir];
			y += dy[dir];
		}
		
		ans = 0;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (visit[i][j] && arr[i][j]){
					ans++;
				}
			}
		}

		printf("Case #%d\n", test);
		printf("%d\n", ans);
	}

	return 0;
}
