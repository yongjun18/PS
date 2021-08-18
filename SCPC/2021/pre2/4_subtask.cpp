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

ll power1 = 37;
ll power2 = 41;

ll powv1[505];
ll powv2[505];

void init(){
	powv1[0] = 1;
	powv2[0] = 1;
	for (int i = 1; i < 505; i++){
		powv1[i] = powv1[i - 1] * power1 % MOD;
		powv2[i] = powv2[i - 1] * power2 % MOD;
	}
}

char str[2000100];
string pat[30100];
char buf[510];

int app[26];
int pv[2000100];
vector<int> patpv[30100];

vector<int> need;

int tmp[2000100];
vector< pair<ll, ll> > len[505];

int main()
{
	int t;

	setbuf(stdout, NULL);
	scanf("%d", &t);
	init();

	for (int test = 1; test <= t; test++){
		int n, k;
		ll ans;

		scanf("%d %d", &n, &k);
		scanf("%s", str);
		for (int i = 0; i < k; i++){
			scanf("%s", buf);
			pat[i] = buf;
		}

		memset(app, -1, sizeof(app));
		for (int i = 0; i < n; i++){
			pv[i] = app[str[i] - 'a'];
			app[str[i] - 'a'] = i;
		}

		for (int p = 0; p < k; p++){
			int siz = pat[p].size();
			patpv[p].resize(siz);
			memset(app, -1, sizeof(app));
			for (int i = 0; i < siz; i++){
				patpv[p][i] = app[pat[p][i] - 'a'];
				app[pat[p][i] - 'a'] = i;
			}
		}

		need.clear();
		for (int p = 0; p < k; p++){
			need.push_back(pat[p].size());
		}
		sort(need.begin(), need.end());
		need.erase(unique(need.begin(), need.end()), need.end());

		for (int it : need){
			ll hashv1, hashv2;
			len[it].clear();
			for (int i = 0; i < n; i++) tmp[i] = 0;

			for (int i = 0; i < it; i++){
				if (pv[i] != -1){
					tmp[pv[i]] = i - pv[i];
				}
			}

			hashv1 = hashv2 = 0;
			for (int i = it - 1; i >= 0; i--){
				hashv1 += powv1[it - 1 - i] * tmp[i] % MOD;
				hashv1 %= MOD;

				hashv2 += powv2[it - 1 - i] * tmp[i] % MOD;
				hashv2 %= MOD;
			}
			len[it].push_back({ hashv1, hashv2 });

			for (int i = it; i < n; i++){
				hashv1 = hashv1 - (tmp[i - it] * powv1[it - 1] % MOD) + MOD;
				hashv1 %= MOD;
				hashv1 *= power1;
				hashv1 %= MOD;

				hashv2 = hashv2 - (tmp[i - it] * powv2[it - 1] % MOD) + MOD;
				hashv2 %= MOD;
				hashv2 *= power2;
				hashv2 %= MOD;

				if (pv[i] != -1 && i - pv[i] <= it - 1){
					tmp[pv[i]] = i - pv[i];

					hashv1 += tmp[pv[i]] * powv1[i - pv[i]] % MOD;
					hashv1 %= MOD;

					hashv2 += tmp[pv[i]] * powv2[i - pv[i]] % MOD;
					hashv2 %= MOD;
				}
				len[it].push_back({ hashv1, hashv2 });
			}
			sort(len[it].begin(), len[it].end());
		}

		ans = 0;
		for (int p = 0; p < k; p++){
			int siz = pat[p].size();
			ll hashv1, hashv2;
			int cnt;

			for (int i = 0; i < siz; i++) tmp[i] = 0;
			for (int i = 0; i < siz; i++){
				if (patpv[p][i] != -1){
					tmp[patpv[p][i]] = i - patpv[p][i];
				}
			}

			hashv1 = hashv2 = 0;
			for (int i = siz - 1; i >= 0; i--){
				hashv1 += powv1[siz - 1 - i] * tmp[i] % MOD;;
				hashv1 %= MOD;

				hashv2 += powv2[siz - 1 - i] * tmp[i] % MOD;
				hashv2 %= MOD;
			}
			cnt = upper_bound(len[siz].begin(), len[siz].end(), make_pair(hashv1, hashv2))
				- lower_bound(len[siz].begin(), len[siz].end(), make_pair(hashv1, hashv2));
			ans += (ll)cnt * (p + 1);
		}

		printf("Case #%d\n", test);
		printf("%lld\n", ans);
	}

	return 0;
}
