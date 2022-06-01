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
int cnt = 0;
Trie tries[1000100];
Trie *new_trie() {
	memset(tries + cnt, 0, sizeof(Trie));
	return &tries[cnt++];
}
Trie* root;

void trie_insert(const string key) {
	Trie* now = root;
	for (int i = 0; i < key.size(); i++) {
		int nxt = key[i] - 'A';
		if (now->go[nxt] == NULL)
			now->go[nxt] = new_trie();
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
	int nxt = ch - 'A';
	while (now != root && now->go[nxt] == NULL)
		now = now->fail;
	if (now->go[nxt])
		now = now->go[nxt];
	pv->go[nxt] = now;

	return now;
}

char str[1000100];
char marker[110];

int main()
{
	int t;

	scanf("%d", &t);

	while (t--) {
		int n, m;
		Trie* now;
		int ans;

		scanf("%d %d", &n, &m);
		scanf("%s", str);
		scanf("%s", marker);

		cnt = 0;
		root = new_trie();
		for (int i = 0; i < m; i++) {
			for (int j = i; j < m; j++) {
				reverse(marker + i, marker + j + 1);
				trie_insert(marker);
				reverse(marker + i, marker + j + 1);
			}
		}
		build_fail();

		now = root;
		ans = 0;
		for (int i = 0; i < n; i++) {
			now = step(now, str[i]);
			if (now->finish) ans++;
		}
		printf("%d\n", ans);
	}

	return 0;
}
