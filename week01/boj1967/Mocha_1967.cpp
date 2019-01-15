/*
 *  BOJ 1967. 트리의 지름
 * 
 *  어떤 node에 대하여 solve 함수를 호출하면,
 *  그 node의 child를 순회하면서 가장 먼 거리를 구하여 리턴한다.
 *  그 과정에서 서브 노드끼리의 거리의 max 값도 확인하면서 전체 max값을 갱신해준다.
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
  int v, w;
};

vector <edge> edges[10050];
bool visited[10050] = {true};
int mx;

int solve(int node) {
  vector <int> dist;  // 각 child에 대하여 가장 먼 거리를 저장하기 위한 vector
  for (auto it : edges[node]) {
    if (visited[it.v]) continue;
    visited[it.v] = true;
    dist.push_back(it.w + solve(it.v)); // 그 child와 연결되는 가중치를 더해줘야 제대로 된 값!
  }

  if (dist.size() == 0) return 0; // leaf이면 0을 리턴
  sort(dist.begin(), dist.end()); // 값 확인을 편하게 하기 위하여 sort를 시행
  mx = max(mx, dist[dist.size() - 1] + (dist.size() > 1 ? dist[dist.size() - 2] : 0));  // 마지막 두 값이 제일 큰 두 값
  return dist[dist.size() - 1]; // 가장 큰 값을 리턴
}

int main(int argc, char *argv[]) {
  int n, u, v, w, i;
  scanf("%d", &n);
  for (i = 0; i < n-1; ++i) {
    scanf("%d %d %d", &u, &v, &w);
    edges[u-1].push_back({v-1, w});
  }
  
  solve(0);
  return !printf("%d\n", mx);
}