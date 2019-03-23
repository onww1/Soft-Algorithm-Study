/*
BOJ 17070 - 파이프 옮기기 1

시간복잡도 : O(N^2)
공간복잡도 : O(N^2)

파이프 옮기기 2 (BOJ 17069)와 같게 풀었습니다.
*/
#include <cstdio>
using namespace std;

int dp[3][16][16];
int arr[16][16];
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

	printf("%d", dp[0][n - 1][n - 1] + dp[1][n - 1][n - 1] + dp[2][n - 1][n - 1]);

	return 0;
}