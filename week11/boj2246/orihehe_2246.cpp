/*
BOJ 2246 - 콘도 선정

시간복잡도 : O(NlogN)
공간복잡도 : O(2^logN)

1번 조건은 1~dX-1에 위치한 콘도들의 숙박비 최솟값보다 cX가 작아야 하고
2번 조건은 1~dX에 위치한 콘도들의 숙박비 최솟값보다 cX가 작아야합니다.
최솟값 세그먼트 트리로 구간의 최솟값을 구해 비교했습니다.
*/
#include <cstdio>
#include <algorithm>
#define pii pair<int,int>
#define MAX 10001
using namespace std;

/* 🐣🐥 */
pii arr[10001];
int tree[32769];
void update(int idx, int s, int e, int k, int val) {
	if (k<s || k>e) return;
	tree[idx] = min(val, tree[idx]);
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2, k, val);
	update(idx * 2+1, (s + e) / 2+1,e, k, val);
}
int get(int idx, int s, int e, int l, int r) {
	if (l > r) return MAX;
	if (r<s || l>e) return MAX;
	if (l <= s && e <= r) {
		return tree[idx];
	}
	return min(get(idx * 2, s, (s + e) / 2, l, r),
		get(idx * 2 + 1, (s + e) / 2 + 1, e, l, r));
}
int main() {
	int n, a, b, cnt = 0;
	scanf("%d", &n);
	fill(tree, tree + 32769, MAX);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		update(1, 1, MAX, a, b);
		arr[i] = { a,b };
	}
	for (int i = 0; i < n; i++) {
		if (get(1, 1, MAX, 1, arr[i].first - 1) > arr[i].second &&
			get(1, 1, MAX, 1, arr[i].first) >= arr[i].second) cnt++;
	}
	printf("%d", cnt);

	return 0;
}