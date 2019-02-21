/*
BOJ 10999 - 구간 합 구하기 2

시간복잡도 : O((M+K)logN)
공간복잡도 : O(2^logN)

Lazy propagation 기초 문제 입니다.
update에서 구간을 완전히 포함한다면 그 노드의 자식들은 탐색하지 않고 lazy배열에 값을 저장합니다.
hap에서는 lazy를 고려하여 구간 합을 구해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

/* 🐣🐥 */
ll *tree, *lazy;
void update(int idx,int s,int e,int l, int r, ll val) {
	if (s > r || e < l) return;
	if (s == e) { // 리프노드일 때
		tree[idx] += val; 
		return;
	}
	// 구간을 완전히 포함한다면 lazy에 변경값 저장
	if (l <= s && e <= r) {
		lazy[idx] += val;
		return;
	}
	// 겹치는 구간만큼만 노드들의 값이 바뀌므로 계산해서 저장
	int kl = max(s, l), kr = min(e, r);
	tree[idx] += val * (kr - kl + 1);
	update(idx * 2, s, (e + s) / 2, l, r, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, val);
}
ll hap(int idx, int s, int e, int l, int r, ll sum) { // sum변수에 거쳐온 lazy배열 값
	if (l > e || r < s) return 0;
	if (s == e) return tree[idx] + sum; // 리프노드
	ll tmp = sum + lazy[idx];
	// 구하려는 구간에 완전히 포함된다면 
	if (l <= s && e <= r) return tree[idx] + tmp * (e - s + 1);
	return hap(idx * 2, s, (e + s) / 2, l, r, tmp)
		+ hap(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, tmp);
}
int main() {
	int n, m, k, h, cm, b, c;
	ll a;
	scanf("%d %d %d", &n, &m, &k);
	h = ceil(log2(n));
	tree = new ll[1 << (h + 1)];
	lazy = new ll[1 << (h + 1)];
	fill(lazy, lazy + (1 << (h + 1)), 0);
	fill(tree, tree + (1 << (h + 1)), 0);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a);
		update(1, 1, n, i, i, a);
	}
	for (int i = 0; i < m + k; i++) {
		scanf("%d", &cm);
		if (cm == 1) {
			scanf("%d %d %lld", &b, &c, &a);
			update(1, 1, n, b, c, a);
		}
		else if (cm == 2) {
			scanf("%d %d", &b, &c);
			printf("%lld\n", hap(1, 1, n, b, c, 0));
		}
	}

	return 0;
}