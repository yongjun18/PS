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
	void print() {
		printf("%d", a.back());
		for (int i = a.size() - 2; i >= 0; i--) {
			for (int b = BASE / 10; b > a[i]; b /= 10)
				printf("0");
			if (a[i] != 0) printf("%d", a[i]);
		}
	}
};

BigInt dp[10100][5];

int main()
{
	int n;

	for (int i = 0; i < 5; i++){
		dp[3][i] = 1;
		if (i == 3) dp[3][i] = 0;
	}
	for (int i = 3; i < 10000; i++){
		dp[i + 1][0] = dp[i + 1][0] + dp[i][0];
		dp[i + 1][2] = dp[i + 1][2] + dp[i][0];

		dp[i + 1][1] = dp[i + 1][1] + dp[i][1];
		dp[i + 1][3] = dp[i + 1][3] + dp[i][1];

		dp[i + 1][0] = dp[i + 1][0] + dp[i][2];
		dp[i + 1][4] = dp[i + 1][4] + dp[i][2];

		dp[i + 1][1] = dp[i + 1][1] + dp[i][3];

		dp[i + 1][4] = dp[i + 1][4] + dp[i][4];
	}

	while (scanf("%d", &n) > 0){
		BigInt res;
		res = 0;
		for (int i = 0; i < 5; i++){
			res = res + dp[n][i];
		}
		res.print();
		printf("\n");
	}

	return 0;
}
