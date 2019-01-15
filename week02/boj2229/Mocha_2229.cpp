/*
 *  BOJ 2229. 조 짜기
 * 
 *  DP[i] : i번째 학생까지 조를 짜주었을 때 조가 잘 짜여진 정도의 최댓값
 *  DP[i] = max{j=1 ~ i} (dp[j-1] + max{k=j ~ i}(a[k]) - min{k=j ~ i}(a[k]))
 * 
 *  DP의 항을 위와 같이 정의하고, i번째 학생의 조를 어떻게 짜줄 때 최대가 되는지를 저장하는 점화식입니다.
 *  i번째 학생부터 j번째 학생까지 max와 min값을 저장하면서 그 차이와 j-1번째까지 짜줬을 때의 최댓값과 더해서 
 *  그 중에서 최대가 나오는 값을 DP에 저장해주는 것입니다.
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int a[1050], dp[1050];
int main() {
  int n, i, j, mx, mn;
  scanf("%d", &n);
  for (i = 1; i <= n; ++i) scanf("%d", a + i);
  for (i = 2; i <= n; ++i) {
    mx = a[i], mn = a[i];
    for (j = i; j > 0; --j) {
      mx = max(mx, a[j]);   // 구간에 대한 max를 갱신
      mn = min(mn, a[j]);   // 구간에 대한 min을 갱신
      // j-1번째까지 조를 짜준 것과 j부터 i번째까지 한 조를 했을 때의 값을 더한 것의 최대를 갱신
      dp[i] = max(dp[i], dp[j-1] + mx - mn);  
    }
  }
  return !printf("%d\n", dp[n]);
}