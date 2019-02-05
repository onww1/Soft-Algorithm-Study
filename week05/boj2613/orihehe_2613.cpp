/*
BOJ 2613 - ���ڱ���

�ð����⵵ : O(NlogN)
�������⵵ : O(N)

�̺�Ž���� mid���� �ִ����� �Ӵϴ�.
�׷��� ���� mid�� ���ϰ� �ǵ��� ������ �׷� ������ �� �׷��� ������ m���϶��,
�տ������� mid�� ���Ϸ� ������ ��ġ�ϸ� �׷��� �����, ���� ���� ������ ���� �׷� ������ ���� ��
������ �׷��� ���� 1������ ��ġ�ϴ� ������� m���� �׷��� ���� �� �ֽ��ϴ�.

���� �׷� ���� m������ �� mid���� amv������ ����, r=mid-1
m�ʰ��� �� �ִ��� �÷��� �ϹǷ�  l=mid+1
*/
#include <cstdio>
using namespace std;

int main() {
	int n, m, l, r, mid, cnt = 0, sum = 0, amv = 0, i;
	int arr[301], ans[301];
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	l = 1, r = 30000;
	ans[0] = 0;
	// �̺�Ž������ �ּҰ� �Ǵ� �ִ��� ã�´�.
	while (l <= r) {  
		mid = (l + r) / 2;
		cnt = 1; sum = 0;
		for (i = 1; i <= n; i++) {
			// i��° ������ cnt�׷쿡 �߰��ص� mid ���϶�� �߰�
			if (sum + arr[i] <= mid) { 
				sum += arr[i];
			}
			else {
				// mid�� ���� �ϳ��� ������ �� ū ���� �� break
				if (sum == 0) break; 
				cnt++; i--;
				sum = 0;
			}
		}
		// �׷��� ���ų�, mid���� ū ������ ���� ��
		if (i <= n || cnt > m) { 
			l = mid + 1;
		}
		else {
			r = mid - 1;
			amv = mid;
		}
	}
	sum = 0; cnt = 1;
	for (i = 1; i <= n; i++) {
		// ���� �׷� ���� ���� ���� ���� ���� �� break
		if (n - i == m - cnt - 1) { 
			cnt++;
			break;
		}
		// �̺�Ž������ ���� �ִ� ���Ϸ� �׷� �����
		if (sum + arr[i] <= amv) { 
			sum += arr[i];
			ans[cnt] = i; // ������ �ε��� ����
		}
		else {
			if (sum == 0) break;
			cnt++; i--;
			sum = 0;
		}
	}
	for (; i <= n; i++) { // ���� �׷��� 1�� ��������
		ans[cnt++] = i;
	}
	printf("%d\n", amv);
	for (int i = 1; i <= m; i++) printf("%d ", ans[i] - ans[i - 1]);

	return 0;
}