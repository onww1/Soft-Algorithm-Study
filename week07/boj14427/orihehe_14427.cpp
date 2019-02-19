/*
BOJ 14427 - 수열과 쿼리 15

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

init에서 트리의 각 노드에 구간의 최솟값을 pair로 <값,인덱스>를 저장했습니다.
renum에서 값이 바뀌는 k를 포함하는 노드값만 갱신해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define pii pair<int,int>
#define MAX 1000000001
using namespace std;

/* 🐣🐥 */
pii arr[1000001], *tree;
pii init(int idx, int l, int r) {
	if (l == r) return tree[idx] = arr[l];
	return tree[idx] = min(init(idx * 2, l, (l + r) / 2)
		,init(idx * 2 + 1, (l + r) / 2 + 1, r));
}
void renum(int idx, int s, int e, int k, int val) {
	if (k > e || k < s) return; // 구간이 k를 포함하고 있지 않다면
	if (s == e) { // 리프노드일 때
		tree[idx].first += val;
		arr[k].first += val;
		return;
	}
	// 자식노드들 탐색
	renum(idx * 2, s, (s + e) / 2, k, val);
	renum(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
	// 현재 트리의 값은 자식 노드들 중 최솟값
	tree[idx] = min(tree[idx * 2], tree[idx * 2 + 1]);
}
int main() {
	int n, m, h, cm, b, c;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].first);
		arr[i].second = i;
	}
	h = ceil(log2(n));
	tree = new pii[1 << (h + 1)];
	init(1, 1, n);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &cm);
		if (cm == 2) {
			// 전체의 최솟값은 노드1에 저장되어있음
			printf("%d\n", tree[1].second);
		}
		else if (cm == 1) {
			scanf("%d %d", &b, &c);
			renum(1, 1, n, b, c - arr[b].first);
		}
	}

	return 0;
}