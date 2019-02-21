/*
BOJ 5676 - 음주 코딩

시간복잡도 : O(KlogN)
공간복잡도 : O(2^logN)

구간 곱의 부호만 구하면 되는 문제입니다.
따라서 음수라면 -1, 양수라면 1, 그리고 0을 각 노드에 저장했습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *tree;
void update(int idx, int s, int e, int k, int val) {
	if (s > k || e < k) return;
	if (s == e) {
		tree[idx] = val;
		return;
	}
	update(idx * 2, s, (e + s) / 2, k, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, k, val);
	tree[idx] = tree[idx * 2] * tree[idx * 2 + 1]; // 자식노드의 곱 저장
}
int mul(int idx, int s, int e, int l, int r) { // 구간 곱 반환
	if (l > e || r < s) return 1;
	if (l <= s && e <= r) return tree[idx];
	return mul(idx * 2, s, (e + s) / 2, l, r)
		* mul(idx * 2 + 1, (e + s) / 2 + 1, e, l, r);
}
int main() {
	int n, m, x, h, a, b;
	char cm;
	h = ceil(log2(100001));
	tree = new int[1 << (h + 1)];
	while (~scanf("%d %d", &n, &m)) {
		fill(tree, tree + (1 << (h + 1)), 0);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if (x == 0) update(1, 1, n, i, x);
			else update(1, 1, n, i, x > 0 ? 1 : -1);
		}
		while (m--) {
			scanf(" %c %d %d", &cm, &a, &b);
			if (cm == 'C') {
				if (b == 0) update(1, 1, n, a, b);
				else update(1, 1, n, a, b > 0 ? 1 : -1);
			}
			else if (cm == 'P') {
				int ans = mul(1, 1, n, a, b);
				if (ans == 0) printf("0");
				else if (ans == -1) printf("-");
				else printf("+");
			}
		}
		printf("\n");
	}

	return 0;
}