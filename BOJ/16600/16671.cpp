#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int choice[100100];
int ptime[100100];

vector<int> jobs[100100];
vector<int> waiting;

int main()
{
    int n, k, need;
    ll sum;

    scanf("%d %d", &n, &k);
    for(int i=0; i<n; i++)
        scanf("%d", &choice[i]);
    for(int i=0; i<n; i++)
        scanf("%d", &ptime[i]);

    for(int i=0; i<n; i++)
        jobs[choice[i]].push_back(ptime[i]);
    for(int i=1; i<=k; i++){
        sort(jobs[i].begin(), jobs[i].end());
        for(int j=(int)jobs[i].size()-2; j>=0; j--)
            waiting.push_back(jobs[i][j]);
    }
    sort(waiting.begin(), waiting.end());

    need = 0;
    for(int i=1; i<=k; i++){
        if(jobs[i].size() == 0)
            need++;
    }
    sum = 0;
    for(int i=0; i<need; i++)
        sum += waiting[i];
    printf("%lld\n", sum);
    return 0;
}
