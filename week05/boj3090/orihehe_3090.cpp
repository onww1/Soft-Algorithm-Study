/*
BOJ 3090 - ���̸� �ּҷ�

�ð����⵵ : O(NlogNlogK)  k=10^9
�������⵵ : O(N)

���� �Է¹��� ������ pq(�ּڰ�)�� �־��ݴϴ�. 
�̺�Ž���� mid���� ������ �ִ����� ����, ���� ���� ���� �̾Ƴ��� �� ���� ���µ�, 
mid������ ���̰� ũ�ٸ� ���� ����+mid ������ �ٲ��ְ� �� ���̸� ī��Ʈ, pq�� �־��ݴϴ�.

���� �ּڰ��� �̾Ƽ� ���� ������ ���� �������� �� �� ������ �ٲ�ٰ� �ص�
���� ���� ���� �� �� �� �ٿ��ְ� ����ؼ� ������ ��ġ�� �˴ϴ�.
*/
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define pii pair<int,int>
using namespace std;

priority_queue<pii, vector<pii>, greater<pii>> q, tmp;
int arr[100002], ans[100002], aa[100002];
int main() {
	int n, l, r, mid;
	ll cnt, t;
	scanf("%d %lld", &n, &t);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		tmp.push({ arr[i],i });
	}
	arr[0] = arr[n + 1] = 0;
	l = 0, r = 1000000000;
	while (l <= r) {
		mid = (l + r) / 2;
		memcpy(aa, arr, sizeof(aa)); // aa�� ���� �迭 arr ����
		cnt = 0;
		q = tmp; // ��� �־�� pq ����
		while (!q.empty()) {
			int nx = q.top().second; q.pop();
			// ����� �� ���� ���̰� mid�̻��̶��
			if (nx - 1 > 0 && aa[nx - 1] - mid > aa[nx]) {
				cnt += aa[nx - 1] - aa[nx] - mid;
				aa[nx - 1] = aa[nx] + mid; // ���� + mid������ ����
				q.push({ aa[nx - 1],nx - 1 }); // �ٲ� ���� pq�� �־���
			}
			if (nx + 1 <= n && aa[nx + 1] - mid > aa[nx]) {
				cnt += aa[nx + 1] - aa[nx] - mid;
				aa[nx + 1] = aa[nx] + mid;
				q.push({ aa[nx + 1],nx + 1 });
			}
			if (cnt > t) break;
		}
		if (cnt > t) {
			l = mid + 1;
		}
		else {
			memcpy(ans, aa, sizeof(ans));
			r = mid - 1;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);

	return 0;
}