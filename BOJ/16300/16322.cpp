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

struct Node{
	string name;
	int idx;
	int price;
	bool operator < (const Node& rhs) const{
		if (price != rhs.price) return price < rhs.price;
		return idx < rhs.idx;
	}
};

vector<Node> candi;

int main()
{
	int l, m;

	scanf("%d %d", &l, &m);
	for (int i = 0; i < m; i++){
		char ch;
		string name;
		int p, c, t, r;
		double avgv;

		while (1){
			scanf("%c", &ch);
			if (ch == '\n') continue;
			if (ch == ',') break;
			name.push_back(ch);
		}
		scanf("%d%*c", &p);
		scanf("%d%*c", &c);
		scanf("%d%*c", &t);
		scanf("%d", &r);

		avgv = (double)t / (t + r) * c * 10080;
		if (avgv < l) continue;

		candi.push_back({ name, i, p });
	}

	sort(candi.begin(), candi.end());

	if (candi.size() == 0){
		printf("no such mower\n");
	}
	else{
		printf("%s\n", candi[0].name.c_str());
		for (int i = 1; i < candi.size(); i++){
			if (candi[i - 1].price != candi[i].price) break;
			printf("%s\n", candi[i].name.c_str());
		}
	}

	return 0;
}
