/*
 *  BOJ 11727. 2xn 타일링 2
 * 
 *  DP[i] : 2xi까지 타일링했을 때의 경우의 수
 *  DP[i] = (DP[i-1] + 2 * DP[i-2]) % MOD
 * 
 *  2xn을 타일링하는 경우의 수를 계산하려면 
 *  2x(n-1)을 타일링한 것의 왼쪽에 세로 타일을 하나 달아주거나
 *  2x(n-2)을 타일링한 것의 왼쪽에 가로 타일 두 개 or 2x2 타일을 하나 놓으면 됩니다.
 *  따라서 위와 같은 점화식이 나옵니다.
 */

#include <cstdio>
#define MOD 10007
using namespace std;

int dp[1050];
int main() {
  int n, i;
  scanf("%d", &n);
  dp[0] = dp[1] = 1;
  for (i = 2; i <= n; ++i)
    dp[i] = (dp[i-1] + 2 * dp[i-2]) % MOD;
  return !printf("%d\n", dp[n]);
}