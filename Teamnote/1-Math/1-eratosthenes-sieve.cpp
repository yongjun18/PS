// minf[x] : x의 소인수 중 가장 작은 값
int minf[1000001];

// O(NloglogN)
void eratos(int n) {
	minf[0] = minf[1] = -1;
	for (int i = 2; i <= n; ++i) minf[i] = i;
	int sqrtn = (int)sqrt((double)n);

	for (int i = 2; i <= sqrtn; ++i) {
		if (minf[i] == i) {
			for (int j = i * i; j <= n; j += i) {
				if (minf[j] == j) minf[j] = i;
			}
		}
	}
}
