/*
 *  BOJ 1949. 우수 마을
 * 
 *  Tree를 하려고 했는데 Tree DP문제가 나오다니요..
 *  일단 이 문제는 DP문제였습니다. 
 * 
 *  DP[i][j] : i번째 node를 우수 마을로 선정(j = 1)하거나, 
 *             선정하지 않았을 때(j = 0)의 최댓값
 *           
 *  DP의 항을 위와 같이 정의를 하고, 임의로 1번 노드에서 출발한다고 했을 때,
 *  1번 노드를 우수 마을로 선정하는 때와 우수 마을로 선정하지 않았을 때의 값을 구하여
 *  그 중에 큰 값을 출력하면 되는 문제였습니다.
 * 
 *  그와 관련된 logic은 solve 함수에 있습니다.
 *  이미 해당 node에서 우수 마을을 선정하는 경우나 선정하지 않는 경우를 구했으면
 *  그 값을 리턴해줍니다. 그것이 아니라면 현재 노드를 기준으로 parent 노드를 제외하고,
 *  child 노드들에 대해서 만약 자신이 우수 마을이라면 child들은 모두 우수 마을이 아니고,
 *  자신이 우수 마을이 아니라면 child들은 우수마을 일수도, 아닐 수도 있다고 생각하고 그 중에 
 *  더 큰 값을 취하도록 하면 됩니다. 
 *  이 상황에 대해서 만약 자신이 우수 마을이 아닌데 다른 child들도 모두 우수 마을이 아닌 경우가 
 *  최대값이 되어 버리면 어떡하나 생각할 수 있는데 주변 마을들이 모두 우수 마을이 아니라면 
 *  무조건 자신이 우수 마을인 경우가 더 큽니다. 따라서 그러한 상황은 최댓값으로 나오지 않습니다.
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> edges[10050];
int a[10050], dp[10050][2];

int solve(int node, int parent, int include) {
  int &ret = dp[node][include];
  if (ret != -1) return ret;    // 만약 이미 확인한 경우라면 그 값을 리턴
  ret = include ? a[node] : 0;  // 이 마을을 우수 마을로 선정하면 인구수를 넣어주고 아니면 0을 넣는다.
  for (auto it : edges[node]) {
    if (it == parent) continue;
    int val = solve(it, node, 0); // child가 우수 마을이 아닌 경우를 구한다.
    if (!include) val = max(val, solve(it, node, 1)); // 만약 이 마을이 우수 마을이 아니라면 
                                                      // child가 우수 마을인 경우도 구해서 비교
    ret += val;
  }
  return ret;
}

int main(int argc, char *argv[]) {
  int n, i, u, v;
  scanf("%d", &n);
  for (i = 1; i <= n; ++i) scanf("%d", a + i);
  for (i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }

  memset(dp, -1, sizeof(dp)); // dp의 값들을 모두 -1로 초기화 
  // 1번 노드에서 출발하여 이것이 우수 마을인 경우와 아닌 경우에 대하여 더 큰 값을 출력
  return !printf("%d\n", max(solve(1, 0, 0), solve(1, 0, 1))); 
}