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
	vector<int> finish;
	int ladies;
};
Trie* root;

void trie_insert(const string &key, int idx) {
	Trie* now = root;
	for (int i = 0; i < key.size(); i++) {
		int nxt = key[i] - 'A';
		if (now->go[nxt] == NULL)
			now->go[nxt] = new Trie();
		now = now->go[nxt];
	}
	now->finish.push_back(idx);
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

				q.push(nxt);
			}
		}
	}
}

Trie* step(Trie* now, char ch) {
	Trie* pv = now;
	int nxt = ch - 'A';
	while (now != root && now->go[nxt] == NULL)
		now = now->fail;
	if (now->go[nxt])
		now = now->go[nxt];
	pv->go[nxt] = now;
	return now;
}

char c[1000100];
int p[1000100];
char buf[1000100];
vector<Trie*> order;
Trie* last[1000100];
int ans[1000100];

int main()
{
	int n, k;

	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf(" %c %d", &c[i], &p[i]);
		p[i]--;
	}
	
	root = new Trie();
	for (int i = 0; i < k; i++) {
		string tmp;
		scanf("%s", buf);
		tmp = buf;
		reverse(tmp.begin(), tmp.end());
		trie_insert(tmp, i);
	}
	build_fail(order);

	last[0] = step(root, c[0]);
	last[0]->ladies++;
	for (int i = 1; i < n; i++) {
		last[i] = step(last[p[i]], c[i]);
		last[i]->ladies++;
	}

	reverse(order.begin(), order.end());
	for (Trie* it : order) {
		for (int q : it->finish) {
			ans[q] = it->ladies;
		}
		it->fail->ladies += it->ladies;
	}

	for (int i = 0; i < k; i++) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
