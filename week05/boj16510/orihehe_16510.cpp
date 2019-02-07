/*
BOJ 16510 - Predictable Queue

�ð����⵵ : O(MlogN)
�������⵵ : O(N)

�迭�� i������ �ɸ��� �ð��� �����صӴϴ�.
�׸����� lower_bound�� x�ð� �̻��� �ּڰ��� ã���ϴ�.
���� lower_bound�� ã�� �ε����� ���� x���� ũ�ٸ� -1�� ����, ���ٸ� �� ���� ������ݴϴ�.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[200002];
int main() {
	int n, m, x, idx;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		arr[i] += arr[i - 1];
	}
	while (m--) {
		scanf("%d", &x);
		idx = lower_bound(arr, arr + n, x) - arr;
		printf("%d\n", idx - (arr[idx] > x ? 1 : 0));
	}

	return 0;
}