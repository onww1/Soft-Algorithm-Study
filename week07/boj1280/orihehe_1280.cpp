/*
BOJ 1280 - 나무 심기

시간복잡도 : O(Nlog200000)
공간복잡도 : O(2^log200000)

세그트리의 각 노드에 구간에 심어진 나무 개수, s부터 구간에 심어진 나무 거리,
r부터 구간에 심어진 나무 거리 정보를 저장합니다.
나무를 심을 때마다 현재 나무의 왼쪽 오른쪽을 나누어 hap에서 거리를 구해줍니다.
그후 나무를 update에서 심어줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define ll long long
#define mod 1000000007
#define MAX 200002
using namespace std;

/* 🐣🐥 */
struct info {
	ll num, lv, rv;
	info() {
		num = lv = rv = 0;
	}
};
info *tree;
int arr[100002];
void update(int idx, int s, int e, int k) { // 현재 나무 k위치에 심는다.
	if (k < s || k > e) return;
	tree[idx].num++; // 현재 구간의 심어진 나무 수
	tree[idx].lv += k - s; // lv에 s부터 k까지의 거리 더함
	tree[idx].rv += e - k; // rv에 r부터 k까지의 거리 더함
	if (s == e) return;
	update(idx * 2, s, (e + s) / 2, k);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, k);
}
ll hap(int idx, int s, int e, int l, int r, int k) {
	if (l > e || r < s) return 0;
	ll tmp;
	if (l <= s && e <= r) {
		// 현재 구간 위치의 오른쪽인지 왼쪽인지, 가까운쪽
		if (abs(s - k) < abs(e - k)) { // 왼쪽에 심어졌다면
			tmp = abs(s - k);
			// k~s거리 * 심어진 나무 수 + lv
			return ((tree[idx].num * tmp)%mod + tree[idx].lv)%mod;
		}
		else {
			tmp = abs(e - k);
			// e~k거리 * 심어진 나무 수 + rv
			return ((tree[idx].num * tmp)%mod + tree[idx].rv)%mod;
		}
	}
	return hap(idx * 2, s, (e + s) / 2, l, r, k)
		+ hap(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, k);
}
int main() {
	int n, h, x;
	ll ans = 1, tmp;
	scanf("%d", &n);
	h = ceil(log2(MAX)) + 1;
	tree = new info[1 << h];
	fill(tree, tree + (1 << h), info());
	scanf("%d", &x);
	update(1, 1, MAX, x + 1);
	for (int i = 1; i < n; i++) {
		scanf("%d", &x);
		// x좌표가 0~200000이기 때문에 구간을 1부터 표시하려 +1한 값을 넣었습니다.
		// 현재 나무 위치의 왼쪽, 오른쪽 거리 합
		tmp = hap(1, 1, MAX, 1, x + 1, x + 1)
			+ hap(1, 1, MAX, x + 1, MAX, x + 1);
		ans = (ans*tmp) % mod;
		update(1, 1, MAX, x + 1);
	}
	printf("%lld", ans);

	return 0;
}