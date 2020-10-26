#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9 + 7;

int arr[100100];
int pos[100100];

int app[100100];
int pvmax[100100];
int nowapp[100100];
int whole[100100];
int other[100100];

void compress(int n){
	vector<int> vec;
	for (int i = 0; i < n; i++){
		vec.push_back(arr[i]);
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());

	for (int i = 0; i < n; i++){
		int p = lower_bound(vec.begin(), vec.end(), arr[i]) - vec.begin();
		pos[i] = p;
		app[p]++;
	}
}

void build(int n){
	for (int i = 0; i < n; i++){
		int p = pos[i];

		if (nowapp[p] == 0 && p > 0){
			pvmax[p] = max(whole[p - 1], nowapp[p - 1]);
		}
		nowapp[p]++;

		other[p] = max(other[p] + 1, pvmax[p] + 1);
		if (p > 0){
			other[p] = max(other[p], nowapp[p - 1] + 1);
			other[p] = max(other[p], whole[p - 1] + 1);
		}

		if (nowapp[p] == app[p]){
			whole[p] = pvmax[p] + app[p];
		}
	}
}

int main()
{
	int n;
	int maxv;
	
	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%d", &arr[i]);
	}
	compress(n);
	build(n);
	
	maxv = 0;
	for (int i = 0; i < n; i++){
		maxv = max(maxv, other[i]);
		maxv = max(maxv, whole[i]);
	}
	printf("%d\n", n - maxv);
	return 0;
}
