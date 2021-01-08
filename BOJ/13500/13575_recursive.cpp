#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>
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

vector<int> arr;

vector<int> get_ans(int k){
	if (k == 1) return arr;
	vector<int> ret(0);
	vector<int> half = get_ans(k / 2);
	
	multiply(half, half, ret);
	if (k & 1) multiply(ret, arr, ret);
	
	while (ret.size() > 0 && ret.back() == 0) ret.pop_back();
	for (int &it : ret) {
		if (it > 0) it = 1;
	}
	return ret;
}

int main()
{
	int n, k;
	vector<int> ans;

	scanf("%d %d", &n, &k);
	arr.resize(1001);

	for (int i = 0; i < n; i++){
		int x;
		scanf("%d", &x);
		arr[x] = 1;
	}

	ans = get_ans(k);
	for (int i = 0; i < ans.size(); i++){
		if (ans[i] > 0){
			printf("%d ", i);
		}
	}
	printf("\n");
	return 0;
}
