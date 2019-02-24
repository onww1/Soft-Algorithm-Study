/*
 *  BOJ 2517. 달리기
 * 
 *  시간 복잡도 : O(NlogN) 
 *  공간 복잡도 : O(N)
 * 
 *  달리기 문제는 머지소트로도 풀 수 있고, 그냥 구간 나눠줘서 따로 업데이트 할 수도 있고, 
 *  현재 저희 주제처럼 인덱스 트리로 구해서 풀 수도 있는 문제였습니다. (많이들 인덱스 트리로 풀죠.)
 * 
 *  값을 받을 때, 그 값의 인덱스도 함께 저장하고, 능력을 오름차순으로 정렬해서 능력이 낮은 애들부터 
 *  등수를 세어 줍니다. 그리고 그 다음 능력의 아이를 볼 때, 자신보다 인덱스가 빠른 애들 중에서 능력이 낮은 애들을 
 *  인덱스 트리를 통해서 확인할 수 있도록 만들었습니다. 
 *  그렇게 최고 등수를 구하여 저장한 후 마지막에 모두 출력했습니다.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

// Fast I/O
const int BUFFER_SIZE = 1 << 18;
char buf[BUFFER_SIZE];
inline char read() {
  static int idx = BUFFER_SIZE;
  if (idx == BUFFER_SIZE) {
    int nidx = fread(buf, 1, BUFFER_SIZE, stdin);
    if (!nidx) return 0;
    idx = 0;
  }
  return buf[idx++];
}
inline int readInt() {
  int sum = 0, flg = 1;
  char now = read();
  while (now == ' ' || now == '\n') now = read();
  if (now == '-') flg = 0, now = read();
  while ('0' <= now && now <= '9') sum = sum * 10 + now - '0', now = read();
  return flg ? sum : -sum;
}
inline ll readLL() {
  ll sum = 0, flg = 1;
  char now = read();
  while (now == ' ' || now == '\n') now = read();
  if (now == '-') flg = 0, now = read();
  while ('0' <= now && now <= '9') sum = sum * 10 + now - '0', now = read();
  return flg ? sum : -sum;
}

const int MAX = 5e5;
int N, tree[MAX + 1], ans[MAX + 1];
pii A[MAX + 1];

void update(int node, int diff);
int sum(int node);

int main(int argc, char *argv[]) {
  N = readInt();
  for (int i = 0; i < N; ++i) A[i] = {readInt(), i + 1};  // 인덱스와 함께 저장

  sort(A, A + N); // 달리기 능력을 오름차순으로 정렬
  for (int i = 0; i < N; ++i) {
    int val = sum(A[i].second - 1); // 자신보다 능력이 좋지 않은 애들 중에 인덱스가 자기보다 빠른 애들을 세줌
    ans[A[i].second] = A[i].second - val; // 자신의 인덱스에 앞선 애들의 수를 빼주면 자신의 최고 등수
    update(A[i].second, 1); // 자신도 나왔음을 기록해둠
  }

  for (int i = 1; i <= N; ++i) printf("%d\n", ans[i]);
  return 0;
}

// 업데이트 함수
void update(int node, int diff) {
  while (node <= N) {
    tree[node] += diff;
    node += node & -node;
  }
}

// 구간 합을 구하는 함수
int sum(int node) {
  int ret = 0;
  while (node > 0) {
    ret += tree[node];
    node -= node & -node;
  }
  return ret;
}