/*
BOJ 11060 - 점프 점프

현재 칸의 숫자만큼 다음 칸들을 살펴봅니다.
(현재 칸에 도달하기 까지 뛴 횟수 + 1)와 (이미 쓰여있는 횟수) 중 최솟값이 다음 칸의 값이 됩니다.
dp[i]에는 현재 칸에 도달할 최소 점프 횟수가 저장되게 됩니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int dp[1002], arr[1002];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	fill(dp, dp + n, 1001);
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		// 현재 칸에 도달할 수 없다면 다음 칸부터는 볼 필요가 없다.
		if (dp[i] == 1001) break; 
		for (int j = 1; j <= arr[i]; j++) {
			if (i + j > 1000) break; // 배열 범위 넘어가면 break
			dp[i + j] = min(dp[i + j], dp[i] + 1);
		}
	}
	if (dp[n - 1] == 1001) printf("-1");
	else printf("%d", dp[n - 1]);

	return 0;
}