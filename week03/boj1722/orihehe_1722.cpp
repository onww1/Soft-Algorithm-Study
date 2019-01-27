/*
BOJ 1722 - ������ ����

�ణ ������ �ڵ� �����ϴ� ��.
������ i��° ������ (n-i)!���� ���� ������� ������ �˴ϴ�.
k��° ������ ���� ���� (k / (n-i)!)��°�� �ִ� ���� ������ָ� �˴ϴ�.

k�� ���� �� ������ ���� ���� �� �� ��°�� ���� ������(cnt)�� ���Ͽ�
(n-i)! * cnt �� �����ָ� �˴ϴ�.
*/
#include <cstdio>
#define ll long long
using namespace std;

int arr[21], ans[21], ap = 1;
int main() {
	int n, cm, cnt = 0;
	ll k = 1, g = 1;
	scanf("%d %d", &n, &cm);
	if (cm == 1) {  // k��° ���� ���ϱ�
		scanf("%lld", &k);
		k--;
		for (int i = 1; i <= n; i++) {
			arr[i] = i;
			g *= i; // n!
		}
		for (int i = n; i >= 1; i--) {
			cnt = 0;
			g /= i;
			for (int j = 1; j <= n; j++) {
				if (arr[j] == 0) continue;  // ���� �� �Ѿ
				if (cnt == k/g) {  // k/(n-i)! ��° �� (for���� i�� �ٸ�)
					ans[ap++] = j;
					arr[j] = 0; // ��������� ǥ��
					break;
				}
				cnt++;
			}
			k %= g;
		}
		for (int j = 1; j <= n; j++) printf("%d ", ans[j]);
	}
	else if (cm == 2) {  // k���ϱ�
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			g *= i;
			ans[i] = i;
		}
		g /= n;
		for (int i = 1; i <= n; i++) {
			cnt = 0;
			for (int j = 1; j <= n; j++) {
				if (ans[j] == 0) continue;  // ���� �� �Ѿ
				if (ans[j] == arr[i]) {
					ans[j] = 0;
					break;
				}
				cnt++; // cnt��°�� ���� ��
			}
			k += g * cnt; 
			if (i != n) g /= (n - i);
		}
		printf("%lld", k);
	}

	return 0;
}