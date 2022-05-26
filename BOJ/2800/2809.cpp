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
	vector< pair<int, Trie*> > adj;
	Trie* fail;
	int finish;

	Trie* go(int nxt) {
		for (auto it : adj) {
			if (it.first == nxt) {
				return it.second;
			}
		}
		return NULL;
	}
};

Trie* root;

void trie_insert(const string key) {
	Trie* now = root;
	for (int i = 0; i < key.size(); i++) {
		int nxt = key[i] - 'a';
		if (now->go(nxt) == NULL) {
			now->adj.push_back({ nxt, new Trie() });
		}
		now = now->go(nxt);
	}
	now->finish = key.size();
}

void build_fail() {
	root->fail = root;
	queue<Trie*> q;

	for (int i = 0; i < 26; i++) {
		Trie* nxt = root->go(i);
		if (nxt != NULL) {
			nxt->fail = root;
			q.push(nxt);
		}
	}
	while (q.size()) {
		Trie* now = q.front(); q.pop();

		for (int i = 0; i < 26; i++) {
			Trie* nxt = now->go(i);
			if (nxt != NULL) {
				Trie* dest = now->fail;
				while (dest != root && dest->go(i) == NULL)
					dest = dest->fail;
				if (dest->go(i)) dest = dest->go(i);
				nxt->fail = dest;

				if (nxt->fail->finish)
					nxt->finish = max(nxt->finish, nxt->fail->finish);
				q.push(nxt);
			}
		}
	}
}

Trie* step(Trie* now, char ch) {
	int nxt = ch - 'a';
	while (now != root && now->go(nxt) == NULL)
		now = now->fail;
	if (now->go(nxt))
		now = now->go(nxt);
	return now;
}

char str[300100];
char bundle[5010];
vector<int> st;

int main()
{
	int n, m;
	Trie* now;

	scanf("%d", &n);
	scanf("%s", str);

	root = new Trie();
	scanf("%d", &m);
	while (m--) {
		scanf("%s", bundle);
		trie_insert(bundle);
	}
	build_fail();

	now = root;
	for (int i = 0; i < n; i++) {
		st.push_back(i);
		now = step(now, str[i]);

		if (now->finish) {
			while (st.size() > 0 && st.back() > i - now->finish) {
				st.pop_back();
			}
		}
	}
	printf("%d\n", st.size());
	return 0;
}
