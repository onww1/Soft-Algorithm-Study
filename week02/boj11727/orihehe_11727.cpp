/*
BOJ 11727 - 2xn 타일링 2

2x1 타일을 뒤에 붙이기 - dp[i-1]
2x2 타일 2가지 경우 (1x2 두 개, 2x2 한 개)를 뒤에 붙이기 - dp[i-2]*2
2x2 경우에 2x1 두 개를 사용하는 경우는 이미 2x1의 경우에서 추가해주니 고려하지 않습니다.
*/
#include <cstdio>
using namespace std;

int dp[1001];
int main() {
	int n;
	scanf("%d", &n);
	dp[1] = 1, dp[2] = 3;
	for (int i = 3; i <= n; i++) {
		dp[i] = (dp[i - 1] + dp[i - 2]*2)%10007;
	}
	printf("%d", dp[n]);

	return 0;
}