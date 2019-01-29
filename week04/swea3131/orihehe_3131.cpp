/*
SWEA 3131 - 100�� ������ ��� �Ҽ�

�ð����⵵ : O(Nlog(logN))
�������⵵ : O(N)

�������׳׽��� ü�� �̿��Ͽ� ������ Ǯ�����ϴ�.
�Ҽ� �迭���� �Ҽ��� ���� ����� ��� true�� ������ִ� ������ �ݺ��մϴ�.
false�� �����ִ� ������ �Ҽ��̰� �˴ϴ�.
*/
#include <cstdio>
#define MAX 1000000
using namespace std;

bool sosu[1000001];
int main() {
	for (int i = 2; i <= MAX; i++) {
		if (sosu[i]) continue;
		printf("%d ", i);
		for (int j = 2; j*i <= MAX; j++) {
			sosu[i*j] = true;
		}
	}

	return 0;
}