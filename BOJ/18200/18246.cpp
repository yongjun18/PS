#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

int n, m;
int arr[1510][1510];
int tree[6100][6100];

void build_y(int xno, int xnl, int xnr, int yno, int ynl, int ynr){
    if(ynl+1 == ynr){
        if(xnl+1 == xnr) tree[xno][yno] = arr[xnl][ynl];
        else tree[xno][yno] = max(tree[2*xno][yno], tree[2*xno+1][yno]);
    }
    else{
        int mid = (ynl+ynr)/2;
        build_y(xno, xnl, xnr, 2*yno, ynl, mid);
        build_y(xno, xnl, xnr, 2*yno+1, mid, ynr);
        tree[xno][yno] = max(tree[xno][2*yno], tree[xno][2*yno+1]);
    }
}
void build_x(int xno, int xnl, int xnr){
    if(xnl+1 != xnr){
        int mid = (xnl+xnr)/2;
        build_x(2*xno, xnl, mid);
        build_x(2*xno+1, mid, xnr);
    }
    build_y(xno, xnl, xnr, 1, 0, m);
}
void build(){ build_x(1, 0, n); }

int query_y(int yl, int yr, int xno, int yno, int ynl, int ynr){
    if(yr <= ynl || ynr <= yl) return -INF;
    if(yl <= ynl && ynr <= yr) return tree[xno][yno];
    int mid = (ynl+ynr)/2;
    return max(query_y(yl, yr, xno, 2*yno, ynl, mid),
        query_y(yl, yr, xno, 2*yno+1, mid, ynr));
}
int query_x(int xl, int xr, int yl, int yr, int xno, int xnl, int xnr){
    if(xr <= xnl || xnr <= xl) return -INF;
    if(xl <= xnl && xnr <= xr) return query_y(yl, yr, xno, 1, 0, m);
    int mid = (xnl+xnr)/2;
    return max(query_x(xl, xr, yl, yr, 2*xno, xnl, mid),
        query_x(xl, xr, yl, yr, 2*xno+1, mid, xnr));
}
int query(int xl, int xr, int yl, int yr){
    return query_x(xl, xr, yl, yr, 1, 0, n);
}

int main()
{
    n = m = 1500;
    int p, q;
    scanf("%d %d", &p, &q);
    for(int i=0; i<p; i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        arr[x1][y1]++;
        arr[x1][y2]--;
        arr[x2][y1]--;
        arr[x2][y2]++;
    }
    for(int i=0; i<n; i++){
        for(int j=1; j<m; j++)
            arr[i][j] += arr[i][j-1];
    }
    for(int j=0; j<m; j++){
        for(int i=1; i<n; i++)
            arr[i][j] += arr[i-1][j];
    }
    build();
    while(q--){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", query(x1, x2, y1, y2));
    }
    return 0;
}
