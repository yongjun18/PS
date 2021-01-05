#include <stdio.h>
#include <memory.h>
#include <stack>
#include <queue>
#include <deque>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int ti[4];
int t;

int scan(){
	int x, y;
	scanf(" %d.%d", &x, &y);
	return x * 100 + y;
}

void print(int x){
	printf("%d.", x / 100);
	x %= 100;
	if (x < 10) printf("0");
	printf("%d\n", x);
}

int tryy(int x){
	vector<int> arr;
	int sum;

	for (int i = 0; i < 4; i++){
		arr.push_back(ti[i]);
	}
	arr.push_back(x);
	sort(arr.begin(), arr.end());

	sum = 0;
	for (int i = 1; i <= 3; i++){
		sum += arr[i];
	}
	return (sum <= t * 3);
}

int main()
{
	int maxv;

	for (int i = 0; i < 4; i++){
		ti[i] = scan();
	}
	t = scan();

	maxv = -1;
	for (int i = 10000; i >= 0; i--){
		if (tryy(i) == 1){
			maxv = i;
			break;
		}
	}

	if (maxv == -1){
		printf("impossible\n");
	}
	else if (maxv == 10000){
		printf("infinite\n");
	}
	else{
		print(maxv);
	}
	return 0;
}
