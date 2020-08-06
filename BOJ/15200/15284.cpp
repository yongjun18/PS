#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int check(int a, int b, int c, int w, int h){
    if(h >= a+c && w >= a+3*b+c) return 1;
    if(h >= a+2*c && w >= 2*b+2*c) return 1;
    return 0;
}

int main()
{
    int a, b, c;
    int w, h;
    int ok = 0;

    scanf("%d %d %d", &a, &b, &c);
    scanf("%d %d", &w, &h);

    for(int i=0; i<2; i++){
        ok |= check(a, b, c, w, h);
        ok |= check(a, c, b, w, h);
        ok |= check(b, a, c, w, h);
        ok |= check(b, c, a, w, h);
        ok |= check(c, a, b, w, h);
        ok |= check(c, b, a, w, h);
        swap(w, h);
    }
    printf("%s\n", ok ? "Yes" : "No");
    return 0;
}
