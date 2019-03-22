/*
BOJ 1461 - 도서관

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

먼 책부터 채워나가는 것이 최소 걸음 수가 됩니다.
그리고 음수 위치의 남은 책이 m보다 작더라도 0에서 음수 책 개수만을 가져가고
돌아와서 최대로 들고 양수쪽으로 가는 것이 최소가 됩니다.
따라서 음수일 경우와 양수일 경우를 따로 봐줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int arr[10001];
int main() {
	int n, m, mp, ans = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);
	for (int i = 0; i < n; i += m) {
		if (arr[i] > 0) break;
		ans += 2 * (-arr[i]);
	}
	for (int i = n - 1; i >= 0; i -= m) {
		if (arr[i] < 0) break;
		ans += 2 * arr[i];
	}
	// 0으로 돌아올 필요가 없으니 큰 값을 빼줍니다.
	ans -= max(abs(arr[0]), abs(arr[n - 1]));

	printf("%d", ans);

	return 0;
}