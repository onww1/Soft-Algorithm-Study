/*
 *  BOJ 1289. 트리의 가중치
 * 
 *  이 문제를 naive하게 풀면 O(n^2)이 나와서 터지게 될 것이라고 생각했습니다.
 *  그래서 최대한 O(n)과 같이 풀 수 있도록 만들어야 겠다고 생각했고,
 *  순회를 하면서 이전까지의 값들을 모두 누적해 나가면 가능할 것 같다고 생각해서 
 *  아래와 같이 풀이를 하였습니다.
 * 
 *  solve 함수를 어떤 노드에 대해서 실행하면 그 노드를 루트로 하는 서브트리에 대해서 
 *  그 노드부터 모든 하위 노드들 까지의 경로에 대한 값들의 합을 리턴하는 것입니다.
 *  그리고 그것을 구하는 과정에서 서브트리 안에서 연결되는 경로에 대한 값들도 전역변수 ans에 
 *  더해 주어서 모든 경우에 대한 값들을 구하도록 하였습니다.
 *  이때 solve를 통해 얻은 값에 1을 더하여 가중치를 곱하는 이유는 그 노드와 1:1로 직접 연결되는 
 *  경우도 카운트해주기 위해서 입니다.
 * 
 *  그리고 서브 트리의 경로에 대한 모든 경우를 구하는 과정에서 만약 서브 노드를 쌍을 지으면서 구했으면 
 *  이것 또한 O(n^2)이기 때문에 문제가 생깁니다. 그래서 이러한 것을 보완하기 위해서 
 *  누적 합에 대해 곱해가는 식으로 했습니다. 
 *  ex) 1, 2, 3, 4의 모든 쌍의 곱의 합을 구하라.
 *    0 * 1 = 0
 *    1 * 2 = 2
 *    (1 + 2) * 3 = 9
 *    (1 + 2 + 3) * 4 = 24
 *    따라서, 0 + 2 + 9 + 24 = 35
 */

#include <cstdio>
#include <vector>
#define MOD 1000000007LL
using namespace std;

typedef long long ll;
struct edge {
  int v;
  ll w;
};

vector <edge> edges[100050];
ll ans = 0LL;

ll solve(int node, int parent) {
  vector <ll> dist; // 각 child에 대한 값들을 저장하기 위한 vector
  for (auto it : edges[node]) {
    if (it.v == parent) continue;
    // child에 대한 solve를 구하고 거기에 1을 더한 다음 가중치를 곱하여 벡터에 저장
    dist.push_back((1LL + solve(it.v, node)) * it.w % MOD); 
  }
  if (dist.size() == 0) return 0LL; // 만약 dist에 아무 것도 없으면 leaf이므로 0을 출력

  // 서브 노드끼리 연결되는 경우에 대한 계산
  ll s = 0LL;
  for (auto it : dist) ans = (ans + (s + 1) * it) % MOD, s = (s + it) % MOD;
  return s;
}

int main(int argc, char *argv[]) {
  int n, i, u, v;
  ll w;
  scanf("%d", &n);
  for (i = 1; i < n; ++i) {
    scanf("%d %d %lld", &u, &v, &w);
    edges[u].push_back({v, w});
    edges[v].push_back({u, w});
  }
  
  solve(1, 0);
  return !printf("%lld\n", ans);
}