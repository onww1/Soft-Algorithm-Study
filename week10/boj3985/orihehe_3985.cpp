/*
BOJ 3985 - 롤 케이크

시간복잡도 : O(L*L)
공간복잡도 : O(L)

원래의 많은 개수, 남은것의 많은 개수를 따로 세주면 됩니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int oi, ri, omx, rmx, arr[1001];
int main() {
	int l, n, a, b, tmp;
	scanf("%d %d", &l, &n);
	for (int i = 1; i <= n; i++) {
		tmp = 0;
		scanf("%d %d", &a, &b);
		// 원래의 가장 많은 조각
		if (omx < b - a + 1) {
			oi = i;
			omx = b - a + 1;
		}
		// 원하는 조각 중 있는 개수를 세준다.
		for (int j = a; j <= b; j++) {
			if (arr[j] == 0) tmp++;
			arr[j] = i;
		}
		if (rmx < tmp) {
			ri = i;
			rmx = tmp;
		}
	}
	printf("%d\n%d", oi, ri);

	return 0;
}