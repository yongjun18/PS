#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

vector< pair<int,int> > arr;

int main()
{
	int n, sum;

	scanf("%d", &n);
	arr.resize(n);

	for(int i=0; i<n; i++){
		scanf("%d", &arr[i].first);
		arr[i].second = i;
	}
	sort(arr.begin(), arr.end());
	reverse(arr.begin(), arr.end());

	sum = 0;
	for(int i=1; i<n; i++)
		sum += arr[i].first;

	if(sum >= arr[0].first){
		for(auto it : arr)
			printf("%d ", it.second + 1);
		printf("\n");
	}
	else printf("impossible\n");

	return 0;
}
