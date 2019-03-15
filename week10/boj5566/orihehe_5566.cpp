/*
BOJ 5566 - 주사위 게임

시간복잡도 : O(N)
공간복잡도 : O(N)

주사위를 굴린만큼 간 후 그 칸의 수만큼 한번 더 가줍니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int arr[1001];
int main() {
	int n, m, cur = 1, x, ans;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		arr[i] = x;
	}
	for (ans = 1; ans <= m; ans++) {
		scanf("%d", &x);
		cur += x; // 주사위 눈 만큼
		cur += arr[cur]; // 칸에 쓰인 만큼
		if (cur >= n) break; // 도착
	}
	printf("%d", ans);

	return 0;
}