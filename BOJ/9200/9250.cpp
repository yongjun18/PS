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
};
Trie* root;

void trie_insert(const string key) {
	Trie* now = root;
	for (int i = 0; i < key.size(); i++) {
		int nxt = key[i] - 'a';
		if (now->go[nxt] == NULL)
			now->go[nxt] = new Trie();
		now = now->go[nxt];
	}
	now->finish++;
}

void build_fail() {
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

Trie* step(Trie* now, char ch) {
	Trie* pv = now;
	int nxt = ch - 'a';
	while (now != root && now->go[nxt] == NULL)
		now = now->fail;
	if (now->go[nxt])
		now = now->go[nxt];
	//	pv->go[nxt] = now;
	return now;
}

char str[10010];

int main()
{
	int n, q;

	scanf("%d", &n);
	root = new Trie();
	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		trie_insert(str);
	}
	build_fail();

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int ok = 0;
		Trie* now = root;
		scanf("%s", str);
		for (int j = 0; str[j]; j++) {
			now = step(now, str[j]);
			if (now->finish == 1) {
				ok = 1;
				break;
			}
		}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}
