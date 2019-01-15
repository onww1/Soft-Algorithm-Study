/*
 *  BOJ 11725. 트리의 부모 찾기
 *
 *  일반적인 트리 문제처럼 트리를 순회하면서 이전 노드를 parent로 저장해주었습니다.
 *  이후, 한 번에 인덱스 순서대로 모두 parent를 출력해주면 되는 것이었습니다.
 */

#include <cstdio>
#include <vector>
using namespace std;

vector <int> edges[100050];
int parent[100050];

void solve(int node, int pa) {
  for (int i : edges[node]) {
    if (i == pa) continue;
    parent[i] = node;     // child의 parent로 자신을 저장.
    solve(i, node);
  }
}

int main(int argc, char *argv[]) {
  int n, i, u, v;
  scanf("%d", &n);
  for (i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  parent[1] = -1;
  solve(1, 0);
  for (i = 2; i <= n; ++i) printf("%d\n", parent[i]);
  return 0;
}