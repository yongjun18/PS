#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int bx[505], by[505];
int ex[505], ey[505];

const int VER = 0;
const int HOR = 1;

struct Seg{
	int bx, by, ex, ey;
	int type;
	bool operator < (const Seg& rhs) const{
		if (type == VER) return bx < rhs.bx;
		else return by < rhs.by;
	}
};

vector<Seg> segv, segh;

int intersect(Seg sv, Seg sh, int& retx, int& rety){
	if (sh.bx < sv.bx && sv.bx < sh.ex){
		if (sv.by < sh.by && sh.by < sv.ey){
			retx = sv.bx;
			rety = sh.by;
			return 1;
		}
	}
	return 0;
}

const int L = 0;
const int D = 1;
const int R = 2;
const int U = 3;

struct Node{
	pair<int, int> nxt[4];
	int is_inter;
	Node() : is_inter(1), nxt{} {}
};

map< pair<int, int>, Node> mp;

vector< pair<int, int> > visit;
vector<ll> tim;

void simulate(){
	pair<int, int> bg = { bx[0], by[0] };
	pair<int, int> now = bg;
	int dir = -1;

	visit.push_back(now);
	if (bx[0] < ex[0]) dir = R;
	if (bx[0] > ex[0]) dir = L;
	if (by[0] < ey[0]) dir = U;
	if (by[0] > ey[0]) dir = D;

	while (visit.size() == 1 || visit.back() != bg){
		now = mp[now].nxt[dir];
		visit.push_back(now);

		if (mp[now].is_inter == 1){
			dir = (dir + 1) % 4;
		}
		else{
			dir = (dir + 2) % 4;
		}
	}
	tim.resize(visit.size(), 0);
	for (int i = 1; i < visit.size(); i++){
		tim[i] = tim[i - 1];
		tim[i] += abs(visit[i - 1].first - visit[i].first);
		tim[i] += abs(visit[i - 1].second - visit[i].second);
	}
}

void print_ans(int t){
	for (int i = 0; i < visit.size(); i++){
		if (tim[i] <= t && t < tim[i + 1]){
			int dx, dy;
			ll more = t - tim[i];

			dx = dy = 0;
			if (visit[i].first < visit[i + 1].first){
				dx = 1;
			}
			if (visit[i].first > visit[i + 1].first){
				dx = -1;
			}
			if (visit[i].second < visit[i + 1].second){
				dy = 1;
			}
			if (visit[i].second > visit[i + 1].second){
				dy = -1;
			}
			printf("%lld %lld\n", visit[i].first + dx * more, visit[i].second + dy * more);
			return;
		}
	}
}

int main()
{
	int n, t;

	scanf("%d %d", &n, &t);
	for (int i = 0; i < n; i++){
		scanf("%d %d %d %d", &bx[i], &by[i], &ex[i], &ey[i]);
	}

	for (int i = 0; i < n; i++){
		if (bx[i] == ex[i]){
			segv.push_back({ bx[i], by[i], ex[i], ey[i], VER });
			if (segv.back().by > segv.back().ey){
				swap(segv.back().by, segv.back().ey);
			}
		}
		else{
			segh.push_back({ bx[i], by[i], ex[i], ey[i], HOR });
			if (segh.back().bx > segh.back().ex){
				swap(segh.back().bx, segh.back().ex);
			}
		}
	}
	sort(segv.begin(), segv.end());
	sort(segh.begin(), segh.end());

	for (int i = 0; i < segh.size(); i++){
		vector< pair<int, int> > dots;
		dots.push_back({ segh[i].bx, segh[i].by });
		for (int j = 0; j < segv.size(); j++){
			int resx, resy;
			if (intersect(segv[j], segh[i], resx, resy)){
				dots.push_back({ resx, resy });
			}
		}
		dots.push_back({ segh[i].ex, segh[i].ey });

		for (int j = 0; j < dots.size(); j++){
			if (j > 0){
				mp[dots[j]].nxt[L] = dots[j - 1];
			}
			if (j + 1 < dots.size()){
				mp[dots[j]].nxt[R] = dots[j + 1];
			}
		}
		mp[*dots.begin()].is_inter = 0;
		mp[*dots.rbegin()].is_inter = 0;
	}

	for (int i = 0; i < segv.size(); i++){
		vector< pair<int, int> > dots;
		dots.push_back({ segv[i].bx, segv[i].by });
		for (int j = 0; j < segh.size(); j++){
			int resx, resy;
			if (intersect(segv[i], segh[j], resx, resy)){
				dots.push_back({ resx, resy });
			}
		}
		dots.push_back({ segv[i].ex, segv[i].ey });

		for (int j = 0; j < dots.size(); j++){
			if (j > 0){
				mp[dots[j]].nxt[D] = dots[j - 1];
			}
			if (j + 1 < dots.size()){
				mp[dots[j]].nxt[U] = dots[j + 1];
			}
		}
		mp[*dots.begin()].is_inter = 0;
		mp[*dots.rbegin()].is_inter = 0;
	}

	simulate();
	print_ans(t % tim.back());

	return 0;
}
