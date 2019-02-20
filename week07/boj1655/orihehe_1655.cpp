/*
BOJ 1655 - 가운데를 말해요

시간복잡도 : O(Nlog20000)
공간복잡도 : O(2^log20000)

사탕상자(2243)와 비슷한 문제입니다.
1~x구간의 합이 k 이상인 가장 작은 x를 찾아줍니다.
정수의 범위가 -10000~10000이므로 10001을 더한 값으로 관리해줬습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *tree;
void update(int idx, int s, int e, int k) {
	if (s > k || e < k) return;
	tree[idx]++;
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2, k);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
int find(int idx, int s, int e, int k) {
	if (s == e) return s;
	if (tree[idx * 2] >= k) return find(idx * 2, s, (e + s) / 2, k);
	else return find(idx * 2 + 1, (s + e) / 2 + 1, e, k - tree[idx * 2]);
}
int main() {
	int n, h, x;
	scanf("%d", &n);
	h = ceil(log2(20002));
	tree = new int[1 << (h + 1)];
	fill(tree, tree + (1 << (h + 1)), 0);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		update(1, 1, 20001, x+10001);
		// 중앙값은 (i+1)/2 번째 수
		printf("%d\n", find(1, 1, 20001, (i + 1) / 2) - 10001);
	}

	return 0;
}