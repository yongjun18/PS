#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF = 1e9;
const int MOD = 1e9+7;

const int MX = 400100;
set<int> tree[MX*4];
void update(int l, int r, int num, int no, int nl, int nr, int add){
    if(r <= nl || nr <= l) return;
    if(l <= nl && nr <= r){
        if(add) tree[no].insert(num);
        else tree[no].erase(num);
        return;
    }
    int mid = (nl+nr)/2;
    update(l, r, num, 2*no, nl, mid, add);
    update(l, r, num, 2*no+1, mid, nr, add);
}
void update(int l, int r, int num, int add){
    update(l, r, num, 1, 0, MX, add);
}
void query(int idx, int no, int nl, int nr, vector<int>& res){
    if(idx < nl || nr <= idx) return;
    for(int it : tree[no]) res.push_back(it);
    if(nl+1 == nr && nl == idx) return;
    int mid = (nl+nr)/2;
    query(idx, 2*no, nl, mid, res);
    query(idx, 2*no+1, mid, nr, res);
}
void query(int idx, vector<int>& res){
    query(idx, 1, 0, MX, res);
}

int n;
int ti[200100];
int xi[200100];
int yi[200100];

vector<int> used;
int sx(int px){
    return lower_bound(used.begin(), used.end(), px)-used.begin();
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %d %d", &ti[i], &xi[i], &yi[i]);
        if(ti[i] == 1){
            used.push_back(xi[i]-yi[i]);
            used.push_back(xi[i]+yi[i]);
        }
        else used.push_back(xi[i]);
    }
    sort(used.begin(), used.end());
    used.erase(unique(used.begin(), used.end()), used.end());

    for(int i=0; i<n; i++){
        if(ti[i] == 1)
            update(sx(xi[i]-yi[i]), sx(xi[i]+yi[i])+1, i, 1);
        else{
            vector<int> tmp;
            int num = -1;
            query(sx(xi[i]), tmp);
            for(int it : tmp){
                ll dx = xi[i]-xi[it];
                ll dy = yi[i]-yi[it];
                if(dx*dx+dy*dy < (ll)yi[it]*yi[it]){
                    num = it;
                    break;
                }
            }
            if(num == -1) printf("-1\n");
            else{
                printf("%d\n", num+1);
                update(sx(xi[num]-yi[num]), sx(xi[num]+yi[num])+1, num, 0);
            }
        }
    }
    return 0;
}
