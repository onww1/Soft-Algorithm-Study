/*
BOJ 2934 - LRH 식물

시간복잡도 : O(NlogM)
공간복잡도 : O(2^logM)

새 식물을 심을 때 줄기부분이 다른 식물의 수평과 교차할 때 꽃이 핍니다.
따라서 심을 때 두개의 줄기 좌표에 수평선분을 세준 뒤 줄기 사이 수평선분에 +1을 해줍니다.
또한 이미 꽃이 피어있다면 다시 피지 않으니, 꽃이 핀 만큼 그 좌표의 수평선분 값을 빼줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAX 100001
using namespace std;

/* 🐣🐥 */
int *tree, *lazy;
void update(int idx, int s, int e, int l, int r, int val) {
	if (r < s || l > e) return;
	if (l <= s && e <= r) {
		lazy[idx] += val;
		return;
	}
	int kr = min(r, e), kl = max(l, s);
	tree[idx] += (kr - kl + 1)*val;
	update(idx * 2, s, (e + s) / 2, l, r, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, val);
}
int getAns(int idx, int s, int e, int k, int sum) {
	if (k > e || k < s) return 0;
	sum += lazy[idx];
	if (s == e) {
		return tree[idx] + sum;
	}
	return getAns(idx * 2, s, (e + s) / 2, k, sum)
		+ getAns(idx * 2 + 1, (e + s) / 2 + 1, e, k, sum);
}
int main() {
	int n, h, a, b;
	scanf("%d", &n);
	h = ceil(log2(MAX)) + 1;
	tree = new int[1 << h];
	fill(tree, tree + (1 << h), 0);
	lazy = new int[1 << h];
	fill(lazy, lazy + (1 << h), 0);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		int ans1 = getAns(1, 1, MAX, a, 0); // 왼쪽 줄기 좌표의 수평선분 개수
		update(1, 1, MAX, a, a, -ans1); // 나온만큼 빼준다.
		int ans2 = getAns(1, 1, MAX, b, 0); // 오른쪽 수평선분 개수
		update(1, 1, MAX, b, b, -ans2); // 나온만큼 빼준다.
		printf("%d\n", ans1 + ans2);
		if (a + 1<b)
			update(1, 1, MAX, a + 1, b - 1, 1);
	}

	return 0;
}