/*
BOJ 2004 - ���� 0�� ����

�ð� ���⵵ : O(logN)
���� ���⵵ : O(1)

nCm -> n! / ((n-m)! * m!)
���ڸ� 0�� 2*5�϶� �ϳ��� ����Ƿ� ���ڿ� �и��� 2�� 5�� ������ �����ݴϴ�.
n!���� x�� ������ n������ x�� ��� ����, x^2�� ��� ����, x^3�� ��� ���� ...�� �˴ϴ�. 
calc�Լ����� �װ��� �����ְ� ����-�и� �� 2�� ����, 5�� ������ ���� ���� ������ݴϴ�.
*/
#include <cstdio>
using namespace std;

int n, m, x2 = 0, x5 = 0, tmp;
// num!�� x����
int calc(int x, int num) {
	int cnt = 0;
	while (num > 0) {
		cnt += num / x;
		num /= x;
	}
	return cnt;
}
int main() {
	scanf("%d %d", &n, &m);
	tmp = n - m;
	x2 += calc(2, n);
	x5 += calc(5, n);
	x2 -= calc(2, m);
	x5 -= calc(5, m);
	x2 -= calc(2, tmp);
	x5 -= calc(5, tmp);

	if (x2 < 0 || x5 < 0) printf("0");
	else printf("%d", x2 > x5 ? x5 : x2);

	return 0;
}