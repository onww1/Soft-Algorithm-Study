/*
BOJ 10164 - 격자상의 경로

로봇은 오른쪽 또는 아래쪽으로만 이동할 수 있습니다.
따라서 특정 지점까지의 경로 수는 로봇이 위에서 오는 경우 + 왼쪽에서 오는 경우 입니다.
이 문제에서 로봇이 반드시 지나가야 할 칸(k)이 주어집니다.
(시작 지점 -> k 의 경로 수) * (k -> 도착지점 의 경로 수)가 최종 경로 수가 됩니다.
만약 k가 없다면 도착지점까지의 경로 수와 같으므로 k에 n*m값을 넣어줍니다.
k지점이 한 줄씩 오른쪽으로 센 칸의 수로 주어지므로 k지점을 2차원 좌표로 바꿔주면
row=(k-1)/m, col=(k-1)%m 이 됩니다.
*/
#include <cstdio>
using namespace std;

int dp[16][16];
int init(int ur, int uc, int dr, int dc) {
	for (int i = ur; i <= dr; i++) dp[i][uc] = 1;
	for (int i = uc; i <= dc; i++) dp[ur][i] = 1;
	for (int i = ur+1; i <= dr; i++) {
		for (int j = uc+1; j <= dc; j++) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[dr][dc];
}
int main() {
	int n, m, k, lu, rd;
	scanf("%d %d %d", &n, &m, &k);
	if (k == 0) k = n * m; k--;
	lu = init(0, 0, k/m, k % m); // k지점의 왼쪽 위 범위 경로 수
	rd = init(k/m, k % m, n-1, m-1); // k지점의 오른쪽 아래 범위 경로 수
	printf("%d", lu*rd);

	return 0;
}