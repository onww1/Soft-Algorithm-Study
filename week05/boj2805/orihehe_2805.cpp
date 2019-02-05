/*
BOJ 2805 - ���� �ڸ���

�ð����⵵ : O(NlogN)
�������⵵ : O(N)

�̺�Ž�������� mid���� �ڸ����� ���̷� �����մϴ�.
�ּ� 0, �ִ� 10���� ���̷� �ڸ� �� �����Ƿ� l=0, r=10�� ���� �����ϰ�,
�Է¹��� �������� ���̿��� mid�� �ڸ� �� ���� �� �ִ� ���� ���̸� sum�� ���մϴ�.
�� sum�� �ʿ��� ���� ���� �̻��̶�� ans�� mid���� ����, �̺�Ž���� ������ �ִ� ���̰� ����ǰ� �˴ϴ�.
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