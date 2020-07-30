#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
vector<int> moim[100100];
int last[100100];
vector<int> adj[100100];
int clean[100100];

int input[100100];
int init[100100];
int infec[100100];

void build_init(){
    memset(last, -1, sizeof(last));
    for(int i=1; i<=n; i++)
        init[i] = input[i];

    for(int i=0; i<m; i++){
        for(int it : moim[i]){
            if(last[it] != -1)
                adj[i].push_back(last[it]);
            last[it] = i;
        }
    }
    for(int i=m-1; i>=0; i--){
        for(int it : moim[i]){
            if(input[it] == 0)
                clean[i] = 1;
        }
        if(clean[i] == 1){
            for(int it : adj[i])
                clean[it] = 1;
        }
    }
    for(int i=0; i<m; i++){
        if(clean[i] == 1){
            for(int it : moim[i])
                init[it] = 0;
        }
    }
}
void simul(){
    for(int i=1; i<=n; i++)
        infec[i] = init[i];
    for(int i=0; i<m; i++){
        int detect = 0;
        for(int it : moim[i]){
            if(infec[it] == 1){
                detect = 1;
                break;
            }
        }
        if(detect == 1){
            for(int it : moim[i])
                infec[it] = 1;
        }
    }
}
int check(){
    for(int i=1; i<=n; i++){
        if(input[i] != infec[i])
            return 0;
    }
    return 1;
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i=0; i<m; i++){
        int k;
        scanf("%d", &k);
        moim[i].resize(k);
        for(int j=0; j<k; j++)
            scanf("%d", &moim[i][j]);
    }
    for(int i=1; i<=n; i++)
        scanf("%d", &input[i]);
    build_init();
    simul();
    if(check()){
        printf("YES\n");
        for(int i=1; i<=n; i++)
            printf("%d ", init[i]);
        printf("\n");
    }
    else printf("NO\n");
    return 0;
}
