/*
BOJ 2517 - 달리기

시간복잡도 : O(NlogN)
공간복잡도 : O(2^log(N))

실력 값을 기준으로 세그를 짜면 터지게됩니다. (10^9)
선수들의 실력은 모두 다르므로 정렬 후 인덱스를 기준으로 세그를 짜줍니다. (500,000)
hap에서 현재 선수의 인덱스 앞에 몇 명이 있는지를 구하고 
현재 인덱스 위치에 update에서 1을 더해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int arr[500001], tmp[500001];
int *tree;
void update(int idx, int s, int e, int k) {
	if (s > k || e < k) return;
	tree[idx]++;
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2, k);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k);
}
int hap(int idx, int s, int e, int l, int r) {
	if (l > e || r < s) return 0;
	if (l <= s && r >= e) return tree[idx];
	return hap(idx * 2, s, (s + e) / 2, l, r)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
int main() {
	int n, h;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		tmp[i] = arr[i];
	}
	h = ceil(log2(n));
	tree = new int[1 << (h + 1)];
	fill(tree,tree + (1 << (h + 1)), 0);
	sort(tmp, tmp + n);
	for (int i = 0; i < n; i++) {
		// 몇 번째로 큰 실력인지
		int idxx = lower_bound(tmp, tmp + n, arr[i]) - tmp;
		// 앞에 본인보다 낮은 실력 명수를 빼줌
		printf("%d\n", i + 1 - hap(1, 1, n, 1, idxx + 1));
		update(1, 1, n, idxx + 1); //  본인 넣어줌
	}

	return 0;
}