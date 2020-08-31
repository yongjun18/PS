// 화성지도 
// https://www.acmicpc.net/problem/3392

const int MX = 30000;
ll cnt[120100];
// area[no] : 해당 노드 아래 켜져 있는 구간의 합집합 길이
ll area[120100];

void update(int l, int r, ll val, int no, int nl, int nr) {
	if (r <= nl || nr <= l) return;
	if (l <= nl && nr <= r) cnt[no] += val;
	else {
		int mid = (nl + nr) / 2;
		update(l, r, val, 2 * no, nl, mid);
		update(l, r, val, 2 * no + 1, mid, nr);
	}
	if (cnt[no] == 0) {
		if (nl + 1 == nr) area[no] = 0;
		else area[no] = area[no * 2] + area[no * 2 + 1];
	}
	else area[no] = nr - nl;
}
void update(int l, int r, ll val, int n) { update(l, r, val, 1, 0, n); }

struct Range {
	int x1, x2, y, v;
	bool operator < (const Range& ot) const {
		if (y != ot.y) return y < ot.y;
		return x1 < ot.x1;
	}
};
vector<Range> rg;

int main()
{
	int n, x1, y1, x2, y2;
	ll sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		rg.push_back({ x1, x2, y1, 1 });
		rg.push_back({ x1, x2, y2, -1 });
	}
	sort(rg.begin(), rg.end());
	for (int i = 0; i < rg.size(); i++) {
		if (i && rg[i].y != rg[i - 1].y)
			sum += area[1] * (rg[i].y - rg[i - 1].y);
		update(rg[i].x1, rg[i].x2, rg[i].v, MX);
	}
	printf("%lld\n", sum);
	return 0;
}
