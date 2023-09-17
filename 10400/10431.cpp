#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

int arr[25];

int main() 
{
	int p;

	scanf("%d", &p);

	while (p--) {
		int tc, ans;
		
		scanf("%d", &tc);
		for (int i = 0; i < 20; i++) {
			scanf("%d", &arr[i]);
		}

		ans = 0;
		for (int i = 1; i < 20; i++) {
			for (int j = 0; j < i; j++) {
				if (arr[j] > arr[i]) {
					ans++;
				}
			}
		}
		printf("%d %d\n", tc, ans);
	}
	return 0;
}
