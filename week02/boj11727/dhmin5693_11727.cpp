/*
 * 우선 n = 1, 2일 때 2*n 직사각형을 채우는 방법은 순서대로 1, 3가지 입니다.
 * 2*3 직사각형을 채우는 방법은 2*1 직사각형에 2*2를 더하거나, 2*2에 긴 타일을 하나 더하는 방법이 있습니다.
 * 이 방법대로 점화식을 세우고 답을 도출했습니다.
 */
#include <cstdio>

int dp[1000] = { 0, };

int main()
{
	int N;
	scanf("%d", &N);

	dp[0] = 1;
	dp[1] = 3;

	for (int i = 2; i < N; i++)
		dp[i] = (dp[i - 1] + dp[i - 2] * 2) % 10007;

	printf("%d\n", dp[N - 1]);
	return 0;
}