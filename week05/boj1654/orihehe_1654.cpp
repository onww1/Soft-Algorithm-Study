/*
BOJ 1654 - 랜선 자르기

시간복잡도 : O(KlogN)   N=int_max
공간복잡도 : O(K)

랜선의 최대 길이를 mid값으로 설정합니다.
최소 1, 최대 2^31-1 이므로 l+r에서 오버플로! long long형으로 값을 구합니다.
설정한 mid값으로 랜선을 잘랐을 때 나오는 랜선 개수는 arr[i]/mid개

mid값으로 자른 랜선의 개수가 필요한 랜선 수보다 많다면 ans에 mid값을 저장하고,
그 때 mid값이 구하려는 최대 길이보다 작거나 같다는 의미이므로 l=mid+1 으로 다음 mid값을 늘려줍니다.
필요한 랜선 수보다 적다면 r=mid-1 으로 다음 mid값을 줄여 랜선 수를 늘려줍니다.
*/
#include <cstdio>
#include <climits>
#define ll long long
using namespace std;

ll arr[10000];
int main() {
	int n, k;
	ll l, r, mid, ans, cnt;
	scanf("%d %d", &k, &n);
	for (int i = 0; i < k; i++) {
		scanf("%lld", &arr[i]);
	}
	l = 1, r = INT_MAX;
	while (l <= r) {
		mid = (l + r) / 2;
		cnt = 0;
		for (int i = 0; i < k; i++) {
			cnt += arr[i] / mid;
		}
		if (cnt >= n) {
			l = mid + 1;
			ans = mid;
		}
		else {
			r = mid - 1;
		}
	}
	printf("%lld", ans);

	return 0;
}