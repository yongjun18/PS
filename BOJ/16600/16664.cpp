#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int dx[8][8];
int dy[8][8];

void build(){
    for(int i=0; i<6; i++){
        for(int j=0; j<7; j++){
            if(j%2 == 0){
                if(i==5) dy[i][j] = 1;
                else dx[i][j] = 1;
            }
            else{
                if(i==0) dy[i][j] = 1;
                else dx[i][j] = -1;
            }
        }
    }
    dx[5][6] = 2;
    dy[5][6] = 0;

    for(int j=1; j<7; j++)
        dy[7][j] = -1;
    dx[7][0] = -1;
    for(int j=0; j<7; j++)
        dy[6][j] = 1;
    for(int i=1; i<7; i++)
        dx[i][7] = -1;
}
void print(int x, int y){
    printf("%c%d ", 'a'+x, y+1);
}
int main()
{
    int n;
    int x = 0;
    int y = 0;

    scanf("%d", &n);
    build();
    print(0, 0);

    for(int i=0; i<n; i++){
        if(i==0 && n==2){
            print(0, 7); print(7, 7);
            break;
        }
        else if(i<=48 && n-i == 3){
            print(6, y); print(6, 7); print(7, 7);
            break;
        }
        else if(49<=i && i<=55 && n-i == 2){
            print(6, 7); print(7, 7);
            break;
        }
        else if(56<=i && n-i == 1){
            print(7, 7);
            break;
        }
        int nx = x + dx[x][y];
        int ny = y + dy[x][y];
        x = nx;
        y = ny;
        print(x, y);
    }
    printf("\n");

    return 0;
}
