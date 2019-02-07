/*
BOJ 11561 - ¡�˴ٸ�

�ð����⵵ : O(TlogK)  K=10��
�������⵵ : O(1)

�ִ��� ¡�˴ٸ��� ���� ��� ���ؼ� �Ÿ��� 1�� �÷����� ������ �˴ϴ�.
���� 1���� x������ ���� n ������ �ִ� x�� ���ϸ� �˴ϴ�.
mid���� x�� �ΰ� �̺�Ž��! 
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