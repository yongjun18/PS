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

struct Trie {
	Trie* go[26];
	Trie* fail;
	int finish;
	int cnt, maxa, depth;
};
Trie* root;

void trie_insert(const string key, vector<int> &a) {
	Trie* now = root;
	root->cnt++;
	
	for (int i = 0; i < key.size(); i++) {
		int nxt = key[i] - 'a';
		if (now->go[nxt] == NULL)
			now->go[nxt] = new Trie();
		now = now->go[nxt];
		now->cnt++;
		now->depth = i + 1;
		now->maxa = max(now->maxa, a[i]);
	}
	now->finish++;
}

void build_fail(vector<Trie*> &ord) {
	root->fail = root;
	queue<Trie*> q;

	for (int i = 0; i < 26; i++) {
		Trie* nxt = root->go[i];
		if (nxt != NULL) {
			nxt->fail = root;
			q.push(nxt);
		}
	}
	while (q.size()) {
		Trie* now = q.front(); q.pop();
		ord.push_back(now);

		for (int i = 0; i < 26; i++) {
			Trie* nxt = now->go[i];
			if (nxt != NULL) {
				Trie* dest = now->fail;
				while (dest != root && dest->go[i] == NULL)
					dest = dest->fail;
				if (dest->go[i]) dest = dest->go[i];
				nxt->fail = dest;

				if (nxt->fail->finish)
					nxt->finish += nxt->fail->finish;
				q.push(nxt);
			}
		}
	}
}

char buf[100100];
string str[100100];
vector<int> arr[100100];
vector<Trie*> order;

void clear(int n) {
	for (int i = 0; i < n; i++) {
		str[i].clear();
		arr[i].clear();
	}
	delete root;
	for (Trie *it : order) {
		delete it;
	}
	order.clear();
}

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int n;
		ll ans;

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", buf);
			str[i] = buf;
		}
		for (int i = 0; i < n; i++) {
			arr[i].resize(str[i].size());
			for (int &it : arr[i]) {
				scanf("%d", &it);
			}
		}

		root = new Trie();
		for (int i = 0; i < n; i++) {
			trie_insert(str[i], arr[i]);
		}
		build_fail(order);

		for (int i = (int)order.size() - 1; i >= 0; i--) {
			Trie *now = order[i];
			now->fail->maxa = max(now->fail->maxa, now->maxa);
		}

		ans = 0;
		for (Trie* it : order) {
			ans = max(ans, (ll)it->cnt * it->maxa * it->depth);
		}
		printf("%lld\n", ans);
		clear(n);
	}
	return 0;
}
