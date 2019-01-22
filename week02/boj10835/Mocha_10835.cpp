/*
 *  BOJ 10835. 카드게임
 * 
 *  DP[i][j] : 왼쪽 더미에서 i번째, 오른쪽 더미에서 j번째에서 시작할 때,
 *             얻을 수 있는 점수의 최댓값
 *  DP[i][j] = max(DP[i+1][j+1], DP[i+1][j])                    (a[i] <= b[j])
 *             max(DP[i+1][j+1], DP[i+1][j], b[j] + DP[i][j+1]) (a[i] > b[j])
 * 
 *  DP 항의 정의와 점화식은 위와 같습니다.
 *  재귀 함수를 사용하여 처음 0, 0에서 깊히 파고들면서 최댓값을 추출해내는 것입니다.
 * 
 *  코드의 형식은 종만북에서 나오는 코드의 형태와 비슷합니다.
 *  탈출 조건은 x == n || y == n입니다. 인덱스가 0에서 시작하기 때문에 n이면 끝값이기 때문입니다.
 *  그리고 ret에 해당 dp의 원소를 참조하게 하고, 만약 dp의 값이 존재한다면 그것을 리턴합니다.
 *  없다면 위의 점화식에 맞게 값을 얻어내도록 합니다.
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[2050], b[2050], dp[2050][2050], n;

int solve(int x, int y) {
  // x나 y가 n이 되면 한 더미가 없어진 것이므로 끝이 납니다.
  if (x == n || y == n) return 0;

  int &ret = dp[x][y];
  if (~ret) return ret; // dp의 값이 존재하면 그 값을 리턴
  ret = max(solve(x + 1, y + 1), solve(x + 1, y));  // 기본적으로 가능한 방법에 대해서 체크
  if (a[x] > b[y]) ret = max(ret, b[y] + solve(x, y + 1)); // 오른쪽 더미를 버릴 수 있는 조건이 충족되면 그것도 확인
  return ret;
}

int main(int argc, char *argv[]) {
  int i;
  scanf("%d", &n);
  for (i = 0; i < n; ++i) scanf("%d", a + i);
  for (i = 0; i < n; ++i) scanf("%d", b + i);
  memset(dp, -1, sizeof(dp));
  return !printf("%d\n", solve(0, 0));
}