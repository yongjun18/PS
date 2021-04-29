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
#include <time.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

const int MX = 101;

struct State{
	char type;
	int r, s, p;
};
int n;
State comp[105];
int csiz[105];
int depth[105];
char allwin[105][105];
char route[105][105];
int last[105];

int mcnt;
State my[50010];

int randv[105];

void build_rand(){
	srand((unsigned int)time(NULL));
	for (int i = 0; i < MX; i++){
		randv[i] = rand() % 3;
	}
}

void build_allwin(int start){
	int now = start;

	for (int i = 1; i <= n; i++){
		depth[i] = 0;
	}
	depth[start] = 1;

	for (int i = 0; i < MX; i++){
		if (comp[now].type == 'R'){
			allwin[start][i] = 'P';
			now = comp[now].p;
		}
		else if (comp[now].type == 'S'){
			allwin[start][i] = 'R';
			now = comp[now].r;
		}
		else if (comp[now].type == 'P'){
			allwin[start][i] = 'S';
			now = comp[now].s;
		}

		if (depth[now] != 0 && csiz[start] == 0){
			csiz[start] = (i + 2) - depth[now];
		}
		if (depth[now] == 0){
			depth[now] = i + 2;
		}
	}
}

void build_route(int start){
	int now = start;
	for (int i = 0; i < MX; i++){
		route[start][i] = comp[now].type;
		if (randv[i] == 0){
			now = comp[now].r;
		}
		if (randv[i] == 1){
			now = comp[now].p;
		}
		if (randv[i] == 2){
			now = comp[now].s;
		}
	}
	last[start] = now;
}

void build_my(int start){
	int now = 1;
	int tmp;
	for (int i = 0; i < MX; i++){
		my[now].type = "RPS"[randv[i]];
		char dir = route[start][i];
		if (dir == 'R'){
			if (my[now].r == 0){
				mcnt++;
				my[now].r = mcnt;
			}
			now = my[now].r;
		}
		else if (dir == 'S'){
			if (my[now].s == 0){
				mcnt++;
				my[now].s = mcnt;
			}
			now = my[now].s;
		}
		else if (dir == 'P'){
			if (my[now].p == 0){
				mcnt++;
				my[now].p = mcnt;
			}
			now = my[now].p;
		}
	}

	if (my[now].r != 0) return;

	tmp = now;
	for (int i = 0; i < MX; i++){
		my[now].type = allwin[last[start]][i];
		if (i < MX - 1){
			mcnt++;
			my[now].r = my[now].s = my[now].p = mcnt;
			now = mcnt;
		}
		else{
			my[now].r = my[now].s = my[now].p = mcnt - (csiz[last[start]] - 1);
		}
	}

}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf(" %c %d %d %d", &comp[i].type, &comp[i].r, &comp[i].p, &comp[i].s);
	}

	build_rand();
	for (int i = 1; i <= n; i++){
		build_allwin(i);
	}
	for (int i = 1; i <= n; i++){
		build_route(i);
	}

	mcnt = 1;
	for (int i = 1; i <= n; i++){
		build_my(i);
	}
	for (int i = 1; i <= mcnt; i++){
		if (my[i].r == 0) my[i].r = i;
		if (my[i].s == 0) my[i].s = i;
		if (my[i].p == 0) my[i].p = i;
	}

	printf("%d\n", mcnt);
	for (int i = 1; i <= mcnt; i++){
		printf("%c %d %d %d\n", my[i].type, my[i].r, my[i].p, my[i].s);
	}
	return 0;
}
