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

int n;
char str[25];
vector< pair<int, int> > blk;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

int meet(int nowx, int nowy, int bx, int by, int d){
	if ((dx[d] == 0 && bx - nowx == 0) || (dx[d] != 0 && (bx - nowx) * dx[d] > 0)){
		if ((dy[d] == 0 && by - nowy == 0) || (dy[d] != 0 && (by - nowy) * dy[d] > 0)){
			return 1;
		}
	}
	return 0;
}

void build(){
	int nowx = 0;
	int nowy = 0;
	int dist = 2;

	for (int i = 0; i < n; i++){
		for (int d = 0; d < 4; d++){
			if ("LRUD"[d] == str[i]){

				for (auto it = blk.begin(); it != blk.end();){
					int bx = it->first;
					int by = it->second;
					if (meet(nowx, nowy, bx, by, d)){
						it = blk.erase(it);
					}
					else it++;
				}

				nowx += dist * dx[d];
				nowy += dist * dy[d];
				blk.push_back({ nowx + dx[d], nowy + dy[d] });
			}
		}
		dist *= 2;
	}

}

int simul(){
	int nowx = 0;
	int nowy = 0;

	for (int i = 0; i < n; i++){
		for (int d = 0; d < 4; d++){
			if ("LRUD"[d] == str[i]){
				int out = 1;

				for (int j = 0; j < blk.size(); j++){
					int bx = blk[j].first;
					int by = blk[j].second;

					if (meet(nowx, nowy, bx, by, d)){
						if (j + 1 == blk.size()){
							if (i == n - 1) return 1;
							else return 0;
						}
						else{
							nowx = bx - dx[d];
							nowy = by - dy[d];
							out = 0;
						}
						break;
					}
				}
				if (out) return 0;
			}
		}
	}
	return 0;
}

int main()
{
	scanf("%s", str);
	n = strlen(str);

	build();

	if (simul()){
		int hx = blk.back().first;
		int hy = blk.back().second;
		blk.pop_back();

		printf("%d %d\n", -hx, -hy);
		printf("%d\n", blk.size());
		for (auto it : blk){
			printf("%d %d\n", it.first - hx, it.second - hy);
		}
	}
	else{
		printf("impossible\n");
	}

	return 0;
}
