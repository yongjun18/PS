#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MX = 100100;
ll weight[MX];
ll wsum[MX * 4];
ll sum[MX * 4];
ll lazy[MX * 4];

ll build(int no, int nl, int nr){
	if(nl+1 == nr) return wsum[no] = weight[nl];
	int mid = (nl+nr)/2;
	return wsum[no] = build(2*no, nl, mid) + build(2*no+1, mid, nr);
}
ll build(int n = MX){ return build(1, 0, n); }

void propagate(int no, int nl, int nr){
	if(nl+1 != nr){
		int mid = (nl+nr)/2;
		sum[2*no] += lazy[no] * wsum[2*no];
		sum[2*no+1] += lazy[no] * wsum[2*no+1];
		lazy[2*no] += lazy[no];
		lazy[2*no+1] += lazy[no];
	}
	lazy[no] = 0;
}

void update(int l, int r, ll val, int no, int nl, int nr){
	if(r <= nl || nr <= l) return;
	if(l <= nl && nr <= r){
		sum[no] += wsum[no] * val;
		lazy[no] += val;
		return;
	}
	propagate(no, nl, nr);
	int mid = (nl+nr) / 2;
	update(l, r, val, 2*no, nl, mid);
	update(l, r, val, 2*no+1, mid, nr);
	sum[no] = sum[2*no] + sum[2*no+1];
}
void update(int l, int r, ll val, int n = MX){ update(l, r, val, 1, 0, n); }

ll query(int l, int r, int no, int nl, int nr){
	if(r <= nl || nr <= l) return 0;
	if(l <= nl && nr <= r) return sum[no];

	propagate(no, nl, nr);
	int mid = (nl+nr)/2;
	return query(l, r, 2*no, nl, mid) + query(l, r, 2*no+1, mid, nr);
}
ll query(int l, int r, int n = MX) { return query(l, r, 1, 0, n); }

struct Query{
	int i, j, k, idx;
	bool operator < (const Query& rhs) const{
		return k < rhs.k;
	}
};

vector<Query> qry1, qry2;
vector<int> used;
ll ans[50100];

int get_cx(int x){
	return lower_bound(used.begin(), used.end(), x) - used.begin();
}
void compress(){
	for(auto it : qry1){
		used.push_back(it.i);
		used.push_back(it.j);
	}
	for(auto it : qry2){
		used.push_back(it.i);
		used.push_back(it.j);
	}
	sort(used.begin(), used.end());
	used.erase(unique(used.begin(), used.end()), used.end());
	
	for(int i=0; i+1<used.size(); i++){
		if(i+1 == used.size()) weight[i] = 1;
		else weight[i] = used[i+1] - used[i];
	}
}

void compute(){
	int now = 0;
	build();
	for(Query q : qry2){
		int l, r;
		while(now < q.k){
			l = get_cx(qry1[now].i);
			r = get_cx(qry1[now].j);
			update(l, r, qry1[now].k);
			now++;
		}
		l = get_cx(q.i);
		r = get_cx(q.j);
		ans[q.idx] = query(l,r);
	}
}

int main() {
	int n;
	
	scanf("%d", &n);
	for(int t=0; t<n; t++){
		int type, i, j, k;
		scanf("%d %d %d %d", &type, &i, &j, &k);
		if(type == 1) qry1.push_back({i, j+1, k, 0});
		else qry2.push_back({i, j+1, k, 0});
	}
	for(int i=0; i<qry2.size(); i++){
		qry2[i].idx = i;
	}
	sort(qry2.begin(), qry2.end());
	compress();
	compute();
	
	for(int i=0; i<qry2.size(); i++){
		printf("%lld\n", ans[i]);
	}
	return 0;
}
