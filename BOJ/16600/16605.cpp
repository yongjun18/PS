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

const int SHU = 1;
const int SOR = 2;

char str1[1001000];
char str2[1001000];

int cnt1, cnt2;
int arr1[1001000];
int arr2[1001000];
int idx1[1001000];
int idx2[1001000];

int shu1[1001000];
int shu2[1001000];

void build1(char str[], int &cnt, int arr[], int idx[]){
	for (int i = 0; str[i]; i++){
		if ('0' <= str[i] && str[i] <= '9'){
			int val = atoi(str + i);
			arr[cnt] = val;
			idx[i] = cnt;
			cnt += 1;
			while ('0' <= str[i] && str[i] <= '9') i++;
		}
	}
}

void check(int type, int x, int y, int arr[], int idx[], int shu[]){
	int ix = x;
	int iy = y;
	while (idx[ix] == -1) ix++;
	while (idx[iy] == -1) iy--;
	if (ix == iy) return;

	sort(arr + idx[ix], arr + idx[iy] + 1);
	if (type == SHU && arr[idx[ix]] != arr[idx[iy]]){
		shu[idx[ix]] = idx[iy];
	}
}
void build2(char str[], int arr[], int idx[], int shu[]){
	int type, x, y, bal;

	for (int i = 0; str[i]; i++){
		if (str[i] == 's'){
			if (str[i + 1] == 'h') type = SHU;
			else type = SOR;

			x = i;
			while (str[x] != '(') x++;

			bal = 1;
			y = x + 1;
			while (1){
				if (str[y] == '(') bal++;
				if (str[y] == ')'){
					bal--;
					if (bal == 0) break;
				}
				y++;
			}
			check(type, x, y, arr, idx, shu);
			i = y;
		}
	}
}

int is_equal(){
	if (cnt1 != cnt2) return 0;
	
	for (int i = 0; i < cnt1; i++){
		if (arr1[i] != arr2[i]){
			return 0;
		}
	}
	for (int i = 0; i < cnt1; i++){
		if (shu1[i] != shu2[i]){
			return 0;
		}
	}
	return 1;
}

int main()
{
	scanf("%s", str1);
	scanf("%s", str2);
	memset(idx1, -1, sizeof(idx1));
	memset(idx2, -1, sizeof(idx2));

	build1(str1, cnt1, arr1, idx1);
	build1(str2, cnt2, arr2, idx2);

	build2(str1, arr1, idx1, shu1);
	build2(str2, arr2, idx2, shu2);

	printf("%s\n", is_equal() ? "equal" : "not equal");

	return 0;
}
