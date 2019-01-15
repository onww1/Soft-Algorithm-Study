/*
 *  BOJ 1068. 트리
 *  
 *  edges라는 int vector의 배열을 만들어서 트리를 입력 받고,
 *  입력받으면서 rt(root)을 저장해서 root를 표기해뒀습니다.
 *  그리고 만약 root가 지워졌으면 leaf는 아예 없으므로 0을 바로 출력하고,
 *  아니라면 stack을 이용하여 dfs를 하면서 leaf이면
 *  count를 증가시켜 주었습니다.
 */

#include <cstdio>
#include <vector>
using namespace std;

vector <int> edges[50];
int main(int argc, char *argv[]) {
  int n, p, i, r, rt;
  
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", &p);            // ith node의 parent
    if (p == -1) rt = i;        // parent가 -1이면 root
    else edges[p].push_back(i); // pth node에 ith node를 child로 추가
  }
  scanf("%d", &r);
  if (r == rt) return !printf("0\n"); // root가 지워졌으면 0 출력

  vector <int> stack;
  stack.push_back(rt);  // root에서 시작하기 위해

  int cnt = 0, node;
  while (!stack.empty()) {
    node = stack.back();
    stack.pop_back();

    // 현재 node의 child가 없거나, 하나 있더라도 그게 지워진 것이면 leaf node
    if (edges[node].size() == 0 || (edges[node].size() == 1 && edges[node][0] == r)) ++cnt;
    else {
      for (auto it : edges[node]) {
        if (it != r) stack.push_back(it); // 지워지는 것을 제외하고 모두 탐색
      }
    }
  }

  return !printf("%d\n", cnt);
}