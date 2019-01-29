/*
BOJ 2018 - 수들의 합 5

시간복잡도 : O(N)
공간복잡도 : O(1)

l~r의 합이 n보다 작다면 r값 증가 후 hap에 더해주고,
n보다 크다면 합에서 l을 빼주고 l을 증가시켜줍니다. 합이 같을 때마다 카운트!
이 과정은 r값 자체가 n보다 커질때 l이 결국 r보다 커지면 종료됩니다.
*/
#include <cstdio>

int main() {
	int n, l, r, hap = 0, cnt = 0;;
	scanf("%d", &n);
	l = r = 0;
	while (l <= r) {
		if (hap <= n) {
			if (hap == n) cnt++;
			hap += ++r;
		}
		else {
			hap -= l++;
		}
	}
	printf("%d", cnt);

	return 0;
}