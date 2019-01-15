/*
 *  BOJ 1693. 트리 색칠하기
 * 
 *  이 문제도 트리 DP였죠...
 * 
 *  DP[i][j] : ith node에 대해서 j를 색칠했을 때,
 *             그 서브 트리의 최솟값 
 * 
 *  이라고 DP를 정의해두고, 트리에 대해서 순회를 하면 됩니다.
 *  1번 노드에서 시작한다고 하고, 1번 노드에 대해서 1~17번 색을 모두 확인해서
 *  그 중에서 가장 작은 값을 출력합니다.
 * 
 *  17개 색을 고정해둔 이유는 이 문제의 입력의 최댓값이 10만인데, 
 *  최대로 나올 수 있는 색의 수를 고민해보니 10만개 이하에 대해서는 
 *  17개의 색만 있으면 된다고 생각했습니다.
 * 
 *  1 -> 1    => 1개 노드
 *  2 -> 2 - 1    => 2개 노드
 *  3 -> 3 - (1) - (2) (1과 2에 대한 상황이 필요)     => 4개 노드
 *  이와 같이 나가면 등비수열의 합이 되고 2^17 - 1 > 100000이므로 17이라고 생각했습니다.
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define INF 1023456789
#define MOD 1000000007LL
using namespace std;

vector <int> edges[100050];
int dp[100050][18];

int solve(int node, int parent, int color) {
  int &ret = dp[node][color];
  if (~ret) return ret;   // 이미 확인한 경우라면 그 값을 리턴
  ret = color;    // 현재 노드를 color 색으로 칠하면 기본적으로 그만큼 필요하므로
  for (auto it : edges[node]) {
    if (it == parent) continue;
    int val = INF;    // min 값을 비교하기 위해 큰 값을 넣어둠.
    for (int c = 1; c <= 17; ++c) {
      if (c == color) continue;
      val = min(val, solve(it, node, c)); // 다른 색에 대하여 최솟값 저장
    }
    ret += val;
  }
  return ret;
}

int main(int argc, char *argv[]) {
  int n, i, u, v, ans = INF;
  scanf("%d", &n);
  for (i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  memset(dp, -1, sizeof(dp));       // dp를 -1로 초기화
  for (i = 1; i <= 17; ++i) {
    ans = min(ans, solve(1, 0, i)); // 모든 색에 대해서 값을 확인하고 최솟값 저장
  }
  return !printf("%d\n", ans);
}