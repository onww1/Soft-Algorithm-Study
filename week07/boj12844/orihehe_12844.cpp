/*
BOJ 12844 - XOR

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

구간 합 구하기 2의 xor버전 입니다.
a>b인 쿼리가 입력으로 주어질 수 있다는 점을 주의합니다. 부들부들..
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *tree, *lazy;
void update(int idx, int s, int e, int l, int r, int val) {
	if (r < s || l > e) return;
	if (l <= s && e <= r) {
		lazy[idx] ^= val;
		return;
	}
	int kl = max(l, s), kr = min(r, e);
	tree[idx] ^= (kr - kl + 1) % 2 * val; // 구간이 홀수개 일때만 xor연산
	update(idx * 2, s, (e + s) / 2, l, r, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, val);
}
int getAns(int idx, int s, int e, int l, int r, int sum) {
	if (l > e || r < s) return 0;
	sum ^= lazy[idx]; // 레이지 값 가져옴
	if (l <= s && e <= r) {
		// 구간이 홀수개 일때만 xor연산
		return tree[idx] ^ ((e - s + 1) % 2 * sum);
	}
	return getAns(idx * 2, s, (e + s) / 2, l, r, sum)
		^ getAns(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, sum);
}
int main() {
	int n, m, h, cm, a, b, c;
	scanf("%d", &n);
	h = ceil(log2(n)) + 1;
	tree = new int[1 << h];
	fill(tree, tree + (1 << h), 0);
	lazy = new int[1 << h];
	fill(lazy, lazy + (1 << h), 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &m);
		update(1, 1, n, i, i, m);
	}
	scanf("%d", &m);
	while (m--) {
		scanf("%d", &cm);
		if (cm == 1) {
			scanf("%d %d %d", &a, &b, &c);
			if (a > b) swap(a, b);
			update(1, 1, n, a + 1, b + 1, c);
		}
		else if (cm == 2) {
			scanf("%d %d", &a, &b);
			if (a > b) swap(a, b);
			printf("%d\n", getAns(1, 1, n, a + 1, b + 1, 0));
		}
	}

	return 0;
}