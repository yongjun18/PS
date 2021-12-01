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

//const int BASE = 10;
//const int BASE_DIGITS = 1;

const int BASE = 1000000000;
const int BASE_DIGITS = 9;

struct BigInt {
	vector<int> a;

	BigInt() { a.push_back(0); }

	BigInt& operator = (long long int v) {
		a.clear();
		while (v > 0) {
			a.push_back(v % BASE);
			v /= BASE;
		}
		return *this;
	}
	BigInt& operator = (const BigInt& ot) {
		a = ot.a;
		return *this;
	}
	BigInt& operator = (const string& s) {
		int x = 0;
		int now = s.size() % BASE_DIGITS;
		if (now == 0) now = BASE_DIGITS;
		a.clear();

		for (char c : s) {
			x *= 10;
			x += c - '0';
			now--;
			if (now == 0) {
				a.push_back(x);
				now = BASE_DIGITS;
				x = 0;
			}
		}
		reverse(a.begin(), a.end());
		return *this;
	}

	bool operator < (const BigInt& ot) const {
		if (a.size() != ot.a.size()) {
			return a.size() < ot.a.size();
		}
		for (int i = (int)a.size() - 1; i >= 0; i--) {
			if (a[i] != ot.a[i]) {
				return a[i] < ot.a[i];
			}
		}
		return false;
	}
	bool operator <= (const BigInt& ot) const {
		if (a.size() != ot.a.size()) {
			return a.size() <= ot.a.size();
		}
		for (int i = (int)a.size() - 1; i >= 0; i--) {
			if (a[i] != ot.a[i]) {
				return a[i] <= ot.a[i];
			}
		}
		return true;
	}
	bool operator == (const BigInt& ot) const {
		return a == ot.a;
	}
	BigInt operator + (const BigInt& ot) const {
		BigInt ret;
		int carry = 0;
		int x = 0;

		ret.a.clear();
		while (1) {
			if (carry == 0 && a.size() <= x && ot.a.size() <= x)
				break;

			ret.a.push_back(carry);
			if (x < a.size()) ret.a[x] += a[x];
			if (x < ot.a.size()) ret.a[x] += ot.a[x];

			carry = ret.a[x] / BASE;
			ret.a[x] %= BASE;
			x++;
		}
		return ret;
	}
	void println() {
		printf("%d", a.back());
		for (int i = (int)a.size() - 2; i >= 0; i--) {
			for (int b = BASE / 10; b > a[i]; b /= 10) printf("0");
			if (a[i] != 0) printf("%d", a[i]);
		}
		printf("\n");
	}
};

char str[1010];
char name[30];
char bet[1010];

vector< pair<BigInt, string> > arr;
vector<string> ans;

int main()
{
	int n;
	BigInt s;
	BigInt now;

	scanf("%d %s", &n, str);
	s = str;

	for (int i = 0; i < n; i++) {
		BigInt b;
		scanf("%s %s", name, bet);
		b = bet;
		arr.push_back({ b, name });
	}
	sort(arr.begin(), arr.end());
	reverse(arr.begin(), arr.end());

	for (int i = 0; i < n; i++) {
		if (now + arr[i].first <= s) {
			now = now + arr[i].first;
			ans.push_back(arr[i].second);
		}
	}
	if (now == s) {
		printf("%d\n", ans.size());
		for (string it : ans) {
			printf("%s\n", it.c_str());
		}
	}
	else printf("0\n");

	return 0;
}
