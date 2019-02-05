/*
BOJ 2110 - ������ ��ġ

�ð����⵵ : O(NlogK)  K=1000000000
�������⵵ : O(N)

���� ������ �� ������ ������ �Ÿ��� mid������ �����մϴ�.
�켱 �� �� ��ǥ�� �����⸦ ��ġ�ϴ� ���� �� ��ǥ�� ������ ��ġ�� �Ÿ��� �ִ밡 �� ���� �ڸ��մϴ�.
���� �� �� ��ǥ�� �ϳ��� ��ġ �ϰ�, ���� ��ǥ���� �ѷ����µ�,
���� ��ǥ�� ���� ��ǥ�� �Ÿ��� mid�� �̻��̶�� �����⸦ ��ġ�ϰ� ī��Ʈ ���ݴϴ�.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[200000];
int main() {
	int n, c, l, r, mid, last, cnt, ans;
	scanf("%d %d", &n, &c);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);
	l = 1, r = 1000000000;
	while (l <= r) {
		mid = (l + r) / 2;
		last = arr[0]; 
		cnt = 1;
		for (int i = 1; i < n; i++) {
			if (arr[i] - last >= mid) {
				cnt++;
				last = arr[i];
			}
		}
		if (cnt >= c) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	printf("%d", ans);

	return 0;
}