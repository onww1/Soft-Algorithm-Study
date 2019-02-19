/*
BOJ 14438 - 수열과 쿼리 17

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

수열과 쿼리 16 문제에서 pair를 int로 바꾸어 풀어줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAX 1000000001
using namespace std;

/* 🐣🐥 */
int arr[1000001], *tree;
int init(int idx, int l, int r) {
	if (l == r) return tree[idx] = arr[l];
	return tree[idx] = min(init(idx * 2, l, (l + r) / 2)
		,init(idx * 2 + 1, (l + r) / 2 + 1, r));
}
void renum(int idx, int s, int e, int k, int val) {
	if (k > e || k < s) return; // 구간이 k를 포함하고 있지 않다면
	if (s == e) { // 리프노드일 때
		tree[idx] += val;
		arr[k] += val;
		return;
	}
	// 자식노드들 탐색
	renum(idx * 2, s, (s + e) / 2, k, val);
	renum(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
	// 현재 트리의 값은 자식 노드들 중 최솟값
	tree[idx] = min(tree[idx * 2], tree[idx * 2 + 1]);
}
int minV(int idx, int s, int e, int l, int r) {
	if (l > e || r < s) return MAX; // 구간을 벗어난다면
	if (l <= s && r >= e) return tree[idx]; // 구간에 포함된다면
	// 자식 노드들 중 최솟값 반환
	return min(minV(idx * 2, s, (s + e) / 2, l, r),
		minV(idx * 2 + 1, (s + e) / 2 + 1, e, l, r));
}
int main() {
	int n, m, h, cm, b, c;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	h = ceil(log2(n));
	tree = new int[1 << (h + 1)];
	init(1, 1, n);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &cm, &b, &c);
		if (cm == 2) {
			printf("%d\n", minV(1, 1, n, b, c));
		}
		else if (cm == 1) {
			renum(1, 1, n, b, c - arr[b]);
		}
	}

	return 0;
}