/*
BOJ 7469 - K번째 수

시간복잡도 : O(M*logK*logN)  K=2*10^9
공간복잡도 : O(N*2^logN)

update에서 세그트리의 각 노드에 현재 구간의 원소를 모두 넣어줍니다.
모든 update를 마치고 각 노드를 정렬해준 후 이분탐색으로 k번째 수를 mid값으로 찾아 num을 호출합니다.
num에서는 세그의 구간이 포함될 때 lower_bound로 val값보다 작은 원소의 개수를 리턴해줍니다.
이러한 트리 형태를 머지소트트리라고 부른다고 합니다!
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define MAX 1000000000
using namespace std;

/* 🐣🐥 */
vector<int> tree[262145];
// 각 노드에 val을 추가 해줍니다.
void update(int idx, int s, int e, int k, int val) {
	if (k<s || k>e) return;
	tree[idx].push_back(val);
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2, k, val);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
}
// val보다 작은 원소 개수를 구하는 함수
int num(int idx, int s, int e, int l, int r, int val) {
	if (r<s || l>e) return 0;
	if (l <= s && e <= r) {
		int ii = lower_bound(tree[idx].begin(), tree[idx].end(), val)
			- tree[idx].begin();
		if (ii == tree[idx].size() || tree[idx][ii]>val) return ii;
		else return ii + 1;
	}
	return num(idx * 2, s, (s + e) / 2, l, r, val)
		+ num(idx * 2 + 1, (s + e) / 2 + 1, e, l, r, val);
}
int main() {
	int n, m, x, a, b, c, le, ri, mid, ans;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		update(1, 1, n, i, x);
	}
	for (int i = 1; i <= 262144; i++) { // 각 노드 정렬
		sort(tree[i].begin(), tree[i].end());
	}
	while (m--) {
		scanf("%d %d %d", &a, &b, &c);
		le = -MAX, ri = MAX;
		while (le <= ri) {
			mid = (le + ri) / 2;
			if (num(1, 1, n, a, b, mid) >= c) {
				ans = mid;
				ri = mid - 1;
			}
			else {
				le = mid + 1;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}