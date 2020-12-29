#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
#include <complex>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

typedef complex<double> base;

void fft(vector <base> &a, bool invert){
	int n = a.size();
	for (int i = 1, j = 0; i<n; i++){
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1){
		double ang = 2 * M_PI / len*(invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i<n; i += len){
			base w(1);
			for (int j = 0; j<len / 2; j++){
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert){
		for (int i = 0; i<n; i++) a[i] /= n;
	}
}
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res){
	vector<base> fa(a.begin(), a.end());
	vector<base> fb(b.begin(), b.end());
	int sum = a.size() + b.size();
	int n = 1;
	while (n < sum) n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);

	for (int i = 0; i<n; i++) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i<n; i++)
		res[i] = int(fa[i].real() + (fa[i].real()>0 ? 0.5 : -0.5));
}

const int MX = 60010;
vector<int> upp, mid, low;

int main()
{
	int u, m, l;
	vector<int> res;
	ll ans;
	
	upp.resize(MX);
	mid.resize(MX);
	low.resize(MX);

	scanf("%d", &u);
	while (u--){
		int x;
		scanf("%d", &x);
		x += 30000;
		upp[x]++;
	}

	scanf("%d", &m);
	while (m--){
		int x;
		scanf("%d", &x);
		x += 30000;
		mid[x]++;
	}

	scanf("%d", &l);
	while (l--){
		int x;
		scanf("%d", &x);
		x += 30000;
		low[x]++;
	}

	multiply(upp, low, res);
	
	ans = 0;
	for (int i = 0; i < MX * 2; i += 2){
		ans += (ll)res[i] * mid[i / 2];
	}
	printf("%lld\n", ans);
	return 0;
}
