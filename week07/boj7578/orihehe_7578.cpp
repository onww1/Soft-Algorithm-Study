/*
BOJ 7578 - 공장

시간복잡도 : O(NlogN)
공간복잡도 : O(2^logN)

식별번호 대신 번호의 인덱스를 기준으로 트리에 넣어줍니다.
arr[x]엔 x식별번호의 인덱스가, tmp[i]엔 B열의 i번째 등장한 식별번호의 A열 인덱스가 저장됩니다.

B열에 있는 기계를 앞에서부터 봐주면서 A열의 인덱스를 트리에 넣어줍니다.
넣을 때마다 현재 식별번호의 A열 인덱스 ~ n까지의 구간합을 더해주면 교차하는 케이블 쌍의 개수가 나오게 됩니다.
B열을 순서대로 봐주니, 현재 식별번호 이전것들의 A열이 현재 A열보다 뒤에 이어져있을 때만 겹치기 때문!
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define ll long long
using namespace std;

/* 🐣🐥 */
int arr[1000001], tmp[500001], *tree;
void update(int idx, int s, int e, int k) {
	if (k > e || k < s) return;
	tree[idx]++;
	if (s == e) return;
	update(idx * 2, s, (e + s) / 2, k);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, k);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
int hap(int idx, int s, int e, int l, int r) {
	if (s > r || e < l) return 0;
	if (s >= l && e <= r) return tree[idx];
	return hap(idx * 2, s, (e + s) / 2, l, r)
		+ hap(idx * 2 + 1, (e + s) / 2 + 1, e, l, r);
}
int main() {
	int n, h, x;
	ll sum = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		arr[x] = i; // arr에 x식별번호 인덱스 저장
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		tmp[i] = arr[x]; // x식별번호 인덱스를 tmp에 저장 B - A (i - tmp[i])
	}
	h = ceil(log2(n));
	tree = new int[1 << (h + 1)];
	fill(tree, tree + (1 << (h + 1)), 0);
	for (int i = 1; i <= n; i++) {
		sum += (ll)hap(1, 1, n, tmp[i], n);
		update(1, 1, n, tmp[i]);
	}
	printf("%lld", sum);

	return 0;
}