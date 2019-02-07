/*
BOJ 11561 - 징검다리

시간복잡도 : O(TlogK)  K=10억
공간복잡도 : O(1)

최대한 징검다리를 많이 밟기 위해서 거리를 1씩 늘려가며 밟으면 됩니다.
따라서 1부터 x까지의 합이 n 이하인 최대 x를 구하면 됩니다.
mid값을 x로 두고 이분탐색! 
*/
#include <cstdio>
#define ll long long
using namespace std;

int main() {
	int t;
	ll n, ans,l,r,mid;
	scanf("%d", &t);
	while (t--) {
		scanf("%lld", &n);
		l = 1, r = 1000000000;
		while (l <= r) {
			mid = (l + r) / 2;
			if (mid*(mid + 1) / 2 <= n) {
				ans = mid;
				l = mid + 1;
			}
			else r = mid - 1;
		}
		printf("%lld\n", ans);
	}

	return 0;
}