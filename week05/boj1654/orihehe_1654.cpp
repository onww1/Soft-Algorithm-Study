/*
BOJ 1654 - ���� �ڸ���

�ð����⵵ : O(KlogN)   N=int_max
�������⵵ : O(K)

������ �ִ� ���̸� mid������ �����մϴ�.
�ּ� 1, �ִ� 2^31-1 �̹Ƿ� l+r���� �����÷�! long long������ ���� ���մϴ�.
������ mid������ ������ �߶��� �� ������ ���� ������ arr[i]/mid��

mid������ �ڸ� ������ ������ �ʿ��� ���� ������ ���ٸ� ans�� mid���� �����ϰ�,
�� �� mid���� ���Ϸ��� �ִ� ���̺��� �۰ų� ���ٴ� �ǹ��̹Ƿ� l=mid+1 ���� ���� mid���� �÷��ݴϴ�.
�ʿ��� ���� ������ ���ٸ� r=mid-1 ���� ���� mid���� �ٿ� ���� ���� �÷��ݴϴ�.
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