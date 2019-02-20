/*
BOJ 1275 - 커피숍2

시간복잡도 : O(MlogN)
공간복잡도 : O(2^log(N))

구간합 구하기 문제와 같은 문제입니다!
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

/* 🐣🐥 */
ll arr[100001], *tree;
void update(int idx, int s, int e, int k, ll val) {
	if (s > k || e < k) return;
	tree[idx]+=val;
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2, k, val);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
ll hap(int idx, int s, int e, int l, int r) {
	if (l > e || r < s) return 0;
	if (l <= s && r >= e) return tree[idx];
	return hap(idx * 2, s, (s + e) / 2, l, r)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
int main() {
	int n, m, h, a, b, c, d;
	scanf("%d %d", &n, &m);
	h = ceil(log2(n));
	tree = new ll[1 << (h + 1)];
	fill(tree, tree + (1 << (h + 1)), 0);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
		update(1, 1, n, i, arr[i]); // 초기화
	}
	while (m--) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		if (a > b) swap(a, b);
		printf("%lld\n", hap(1, 1, n, a, b));
		update(1, 1, n, c, d-arr[c]);
		arr[c] = d;
	}

	return 0;
}