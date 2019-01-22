/*
 *  BOJ 2449. 전구
 * 
 *  DP[i][j] : i번째 ~ j번째 전구까지 같은 색으로 바꾸는 데 드는 최소 비용
 *  DP[i][j] = min {k = i~j-1} (DP[i][k] + DP[k+1][j] + if color[i] == color[k+1] 0, else 1)
 * 
 *  우선, 입력을 받을 때, 연속되는 같은 색은 무시하여 입력을 압축시켰습니다.
 *  그런 다음, 그 입력받은 범위에 대해서 solve 함수를 호출시키고, 그 값을 출력하였습니다.
 *  solve 함수는 들어오는 범위 [s, e]에 대하여 최소 변환 횟수를 반환하는 함수입니다.
 *  
 *  solve 함수의 경우 먼저 탈출 조건으로 s == e가 있는데, 이것은 단 하나의 전구에 대해서는
 *  무조건 같은 색이므로 변환 횟수가 0입니다. 그 다음, 만약 한 번 확인했던 케이스면 그 값을 리턴합니다.
 *  만약 아직 확인하지 못한 케이스라면 먼저 최솟값을 구하는 문제이므로 큰 값을 넣은 다음,
 *  그 영역을 둘로 쪼개어서 변환시킬 때, 어떤 경우가 가장 적은 변환을 필요로 하는지 구해 저장합니다.
 *  이 때, 색을 변환한다는 것은 첫 번째 색으로 변환시킨다고 했을 때를 기준으로 했습니다.
 *  따라서 만약 두 영역의 첫 번째 색이 똑같으면 변환 수가 증가하지 않고, 다르다면 한 번 변환시켜야 합니다.
 *  이러한 방식으로 최종적으로 전체 영역에 대한 최솟값을 구할 수 있습니다.
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x7f7f7f7f
using namespace std;

int color[205], dp[205][205];

int solve(int s, int e) {
  if (s == e) return 0; // 탈출 조건
  int &ret = dp[s][e];
  if (~ret) return ret; // 이미 구한 적 있으면 그 값을 리턴
  ret = INF;  // 최솟값을 구하는 문제이므로 큰 값을 대입
  // 행렬 연산 순서 문제와 같이 두 부분으로 쪼개서 어떨 때 최소인지 구하는 것입니다.
  for (int k = s; k < e; ++k) { 
    int offset = (color[s] == color[k+1] ? 0 : 1);  // 첫 색이 다르면 변환 횟수가 하나 더 필요합니다.
    ret = min(ret, solve(s, k) + solve(k+1, e) + offset); // 최솟값을 구합니다.
  }
  return ret;
}

int main(int argc, char *argv[]) {
  int n, k, i, cnt;
  scanf("%d %d", &n, &k);
  // 이전 색이랑 비교하면서 다를 때만 cnt를 증가시켜 원소의 수를 줄입니다.
  for (i = 0, cnt = 0; i < n; ++i) {
      scanf("%d", color + cnt);
      if (!cnt || (color[cnt-1] != color[cnt])) ++cnt;
  }
  memset(dp, -1, sizeof(dp));
  return !printf("%d\n", solve(0, cnt-1));
}