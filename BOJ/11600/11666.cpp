#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

struct Point{
	int x, type;
	bool operator < (const Point& rhs) const{
		if(x != rhs.x) return x < rhs.x;
		return type < rhs.type;
	}
};

vector<Point> pt;
queue<int> que;

int main()
{
	int n, m;
	int ans;

	scanf("%d %d", &n, &m);
	for(int i=0; i<n; i++){
		int a, s;
		scanf("%d %d", &a, &s);
		pt.push_back({a, 1});
		pt.push_back({a+s, -1});
	}
	sort(pt.begin(), pt.end());

	ans = 0;
	for(Point p : pt){
		if(p.type == -1){
			que.push(p.x);
		}
		else{
			while(que.size() > 0 && p.x - que.front() > m){
				que.pop();
			}
			if(que.size() > 0){
				que.pop();
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
