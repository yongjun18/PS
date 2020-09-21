#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char tmp[30];
vector<string> s;
vector<int> cor, incor;

vector<string> ans;
int correct;

int only_one(){
	correct = 1;
	for(int i=0; i<s.size(); i++){
		if(cor[i] + incor[i] > 1)
			return 0;
		if(incor[i] == 1)
			correct = 0;
	}
	return 1;
}

int main()
{
	int n, m;

	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%s", tmp);
		s.push_back(tmp);
	}
	cor.resize(n);
	incor.resize(n);
	ans.resize(n);

	scanf("%d", &m);
	while(m--){
		string d, e, c;

		scanf("%s", tmp); d = tmp;
		scanf("%s", tmp); e = tmp;
		scanf("%s", tmp); c = tmp;

		for(int i=0; i<n; i++){
			if(s[i] == d){
				if(ans[i].size() == 0)
					ans[i] = e;
				if(c[0] == 'c') cor[i]++;
				else incor[i]++;
			}
		}
	}

	if(only_one()){
		for(int i=0; i<s.size(); i++)
			printf("%s ", ans[i].c_str());
		printf("\n");
		if(correct == 1) printf("correct\n");
		else printf("incorrect\n");
	}
	else{
		ll corcnt = 1;
		ll totcnt = 1;
		for(int i=0; i<n; i++){
			corcnt *= cor[i];
			totcnt *= cor[i] + incor[i];
		}
		printf("%lld correct\n", corcnt);
		printf("%lld incorrect\n", totcnt - corcnt);
	}
	return 0;
}
