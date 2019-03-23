/*
BOJ 17069 - 파이프 옮기기 2

시간복잡도 : O(N^2)
공간복잡도 : O(N^2)

dp[방향][r][c] 로 설정해줍니다.
먼저 맨 윗줄은 오른쪽방향만 가능하므로 벽이 나오기 전까지 1로 채워줍니다.

그리고나서 두번째 줄부터 각 칸에 대해 장애물이 없다면 봐주는데
오른쪽 - 오른쪽, 대각선에서 온 왼쪽칸까지의 경우
아래 - 아래, 대각선에서 온 위쪽 칸까지의 경우
대각선 - 오른쪽, 아래, 대각선에서 온 왼위대각까지의 경우를 더해줍니다.
대각선의 경우 왼쪽과 위의 벽 여부도 체크해줍니다.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

ll dp[3][35][35];
int arr[35][35];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	dp[0][0][1] = 1;
	for (int i = 2; i < n; i++) {
		if (!arr[0][i])
			dp[0][0][i] = dp[0][0][i - 1];
	}
	for (int i = 1; i<n; i++) {
		for (int j = 1; j<n; j++) {
			if (!arr[i][j]) {
				if (!arr[i - 1][j] && !arr[i][j - 1]) {
					dp[2][i][j] += dp[2][i - 1][j - 1] + dp[0][i - 1][j - 1] + dp[1][i - 1][j - 1];
				}
				dp[1][i][j] += dp[2][i - 1][j] + dp[1][i - 1][j];
				dp[0][i][j] += dp[2][i][j - 1] + dp[0][i][j - 1];
			}
		}
	}

	printf("%lld", dp[0][n - 1][n - 1] + dp[1][n - 1][n - 1] + dp[2][n - 1][n - 1]);

	return 0;
}