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

const int MX = 300100;
ll tree[2 * MX];

void build() {
	for (int i = 0; i < MX; i++)
		tree[MX + i] = INF;
	for (int i = MX - 1; i > 0; i--)
		tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
}
void update(int idx, ll val) {
	idx += MX;
	for (tree[idx] = min(tree[idx], val); idx > 1; idx >>= 1)
		tree[idx >> 1] = min(tree[idx], tree[idx ^ 1]);
}
ll query(int l, int r) {
	ll res = INF;
	for (l += MX, r += MX; l < r; l >>= 1, r >>= 1) {
		if (l & 1) res = min(res, tree[l++]);
		if (r & 1) res = min(res, tree[--r]);
	}
	return res;
}

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
	now->finish = key.size();
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

				if (nxt->fail->finish) {
					nxt->finish = max(nxt->finish, nxt->fail->finish);
				}
				q.push(nxt);
			}
		}
	}
}

Trie* step(Trie* now, char ch) {
	int nxt = ch - 'a';
	while (now != root && now->go[nxt] == NULL)
		now = now->fail;
	if (now->go[nxt])
		now = now->go[nxt];
	return now;
}

char ransom[300100];
char str[300100];

int main()
{
	int l, len;
	Trie *now;
	ll ans;

	scanf("%d", &l);
	scanf("%s", ransom + 1);
	len = strlen(ransom + 1);

	root = new Trie();
	for (int i = 0; i < l; i++) {
		scanf("%s", str);
		trie_insert(str);
	}
	build_fail();

	build();
	update(0, 0);
	
	now = root;
	for (int i = 1; i <= len; i++) {
		now = step(now, ransom[i]);
		if (now->finish) {
			ll minv = query(i - now->finish, i);
			update(i, minv + 1);
		}
	}

	ans = query(len, len + 1);
	if (ans < INF) {
		printf("%lld\n", query(len, len + 1));
	}
	else printf("-1\n");
	return 0;
}
