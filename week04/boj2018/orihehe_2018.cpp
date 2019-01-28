/*
BOJ 2018 - ������ �� 5

�ð����⵵ : O(N)
�������⵵ : O(1)

l~r�� ���� n���� �۴ٸ� r�� ���� �� hap�� �����ְ�,
n���� ũ�ٸ� �տ��� l�� ���ְ� l�� ���������ݴϴ�. ���� ���� ������ ī��Ʈ!
�� ������ r�� ��ü�� n���� Ŀ���� l�� �ᱹ r���� Ŀ���� ����˴ϴ�.
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