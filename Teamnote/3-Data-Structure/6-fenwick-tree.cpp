int fenn;
// 반드시 1-indexed array를 사용해야 함
// fenwick[i] : i번 원소까지 (i & -i)개 원소들에 더해져 있는 값
ll fenwick[100001];

// x번 원소의 값 쿼리
ll query(int x) {
	ll sum = 0;
	while (x <= fenn) {
		sum += fenwick[x];
		x += (x & -x);
	}
	return sum;
}

// [1, x] 구간에 val 값을 더한다.
void update(int x, ll val) {
	while (x > 0) {
		fenwick[x] += val;
		x -= (x & -x);
	}
}

// [x, y] 구간에 val값을 더한다.
void update(int x, int y, ll val) {
	update(y, val);
	update(x - 1, -val);
}
