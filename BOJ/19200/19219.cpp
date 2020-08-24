#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

char str[300100];
vector<char> comp;
vector<int> len;

int check(){
    if(comp.size() % 2 == 0)
        return 0;
    if(len[len.size()/2] < 2)
        return 0;

    for(int i=0; i<len.size()/2; i++){
        int j = len.size()-1-i;
        if(comp[i] != comp[j])
            return 0;
        if(len[i] + len[j] < 3)
            return 0;
    }
    return 1;
}
int main()
{
    scanf("%s", str);
    for(int i=0; str[i]; i++){
        if(i == 0 || str[i-1] != str[i]){
            comp.push_back(str[i]);
            len.push_back(1);
        }
        else len.back() += 1;
    }
    if(check() == 1)
        printf("%d\n", len[len.size()/2] + 1);
    else printf("0\n");
    return 0;
}
