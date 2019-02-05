/*
BOJ 2805 - 나무 자르기

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

이분탐색에서의 mid값을 자르려는 높이로 설정합니다.
최소 0, 최대 10억의 높이로 자를 수 있으므로 l=0, r=10억 으로 설정하고,
입력받은 나무들의 높이에서 mid로 자를 때 얻을 수 있는 나무 길이를 sum에 구합니다.
그 sum이 필요한 나무 길이 이상이라면 ans에 mid값을 저장, 이분탐색이 끝나면 최대 높이가 저장되게 됩니다.
*/
#include <cstdio>
#define ll long long
using namespace std;

ll tree[1000001];
int main() {
	int n, m;
	ll l, r, mid, sum = 0 , ans;
	scanf("%d %d", &n, &m);
	l = 0, r = 1000000000;
	for (int i = 0; i < n; i++) {
		scanf("%lld", &tree[i]);
	}
	while (l <= r) {
		mid = (l + r) / 2;
		sum = 0;
		for (int i = 0; i < n; i++) {
			if (tree[i] - mid > 0) sum += tree[i] - mid;
		}
		if (sum >= m) {
			ans = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	printf("%lld", ans);

	return 0;
}