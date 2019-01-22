/*
 * 확률과 통계에서 길 찾는 방법의 수 공식을 사용해서 풀었습니다.
 * DP -> 공식 활용 -> DP로 돌리느라 3번만에 성공했네요...
 *
 * 공식은 도착점으로 가기 위한 오른쪽 방향이 x, 아래 방향이 y라 한다면 (x + y)! / (x! * y!)입니다.
 * 공식 활용해서 풀 수도 있겠지만 (x + y)가 최대 28!이므로 하나의 변수에 저장하기는 어려운 값이 나오게 됩니다.
 *
 * 한 지점으로 갈 때 가는 경우의 수는 목표점의 윗 지점으로 가는 경우의 수 + 왼쪽 지점으로 가는 경우의 수로 구할 수 있습니다.
 * 또한 어느 한 지점을 반드시 포함해야 한다면, 출발점에서 그 지점까지 경우의 수와 그 지점부터 도착점까지 경우의 수를 곱하면 됩니다.
 * 이 방법을 활용해서 DP로 구성했습니다.
 */
#include <cstdio>
using namespace std;

typedef long long int lli;

lli dp[16][16] = { 0, };

void calc(int startY, int startX, int endY, int endX) {
	// 윗 지점과 왼쪽 지점을 초기화하여 현재 지점을 1로 시작할 수 있게 하였음.
	dp[startY][startX - 1] = 0;
	dp[startY - 1][startX] = 1;

	for (int i = startY; i <= endY; ++i) {
		for (int j = startX; j <= endX; ++j) {
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
}

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	// k가 0인 경우 무조건 (n, m)을 도착점으로 정합니다.
	if (k == 0) {
		calc(1, 1, n, m);
		printf("%lld\n", dp[n][m]);
		
		return 0;
	}

	// 받은 k가 몇 행의 몇 열인지를 구하고 도착점으로 설정합니다.
	int row = k / m + 1;
	int col = k % m;

	// 가장 마지막 열은 값 보정이 필요합니다.
	if (k % m == 0) {
		--row, col = m;
	}

	// (1, 1) ~ (row, col)까지 경우의 수를 구합니다.
	calc(1, 1, row, col);
	lli ans = dp[row][col];

	// (row, col) ~ (n, m)까지 경우의 수를 구하고 앞서 구한 경우의 수를 곱하여 답을 도출합니다.
	calc(row, col, n, m);
	printf("%lld\n", ans * dp[n][m]);

	return 0;
}