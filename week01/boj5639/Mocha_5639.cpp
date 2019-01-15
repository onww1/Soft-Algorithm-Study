/*
 *  BOJ 5639. 이진 검색 트리
 * 
 *  preorder는 현재 노드의 값부터 출력하고, 왼쪽 -> 오른쪽 순으로 출력합니다.
 *  그렇다는 것은 겹치는 값이 없는 트리에서 전위 순회를 했을 때,
 *  현재 값을 출력하고, 그 이후에 나오는 값중에서 현재 값보다 작은 것들은 왼쪽 서브트리,
 *  현재 값보다 큰 것들은 오른쪽 서브트리임을 알 수 있습니다.
 *  따라서 현재 값을 기준으로 이후의 영역에 대하여 lower_bound를 하여
 *  현재 값보다 큰 값중 가장 왼쪽에 있는 것을 찾고, 그것을 기준으로 나누어서 재귀적으로 실행하면 됩니다.
 *  그렇게 하여 왼쪽, 오른쪽, 현재값 순으로 출력하면 postorder 순회를 구현할 수 있습니다.
 */

#include <cstdio>
using namespace std;

int a[10050], n;

// s : 현재 값의 인덱스, e : 현재 영역의 다음 인덱스
// 현재 값은 a[s]이고, 탐색할 영역은 [s+1, e)입니다.
void solve(int s, int e) {
  if (s >= e) return;  // s >= e이면 탐색할 영역이 없는 것이므로 return!

  // lower bound logic
  // 최종적으로 r이 a[s]보다 큰 값중 가장 왼쪽 원소의 인덱스를 가지고 있습니다.
  int l = s + 1, r = e;
  while (l < r) {
    int m = (l + r) / 2;
    if (a[m] > a[s]) r = m;
    else l = m + 1;
  }

  solve(s + 1, r);      // 왼쪽 서브트리 순회
  solve(r, e);          // 오른쪽 서브트리 순회
  printf("%d\n", a[s]); // 현재값 출력
}

int main(int argc, char *argv[]) {
  while (~scanf("%d", &a[n++]));  // EOF 만날 때까지 입력,
  solve(0, n-1);  // e는 포함하지 않는 값이지만, n-1인 이유는 EOF 때문에 n이 하나 더 증가했기 때문.
  return 0;  
}