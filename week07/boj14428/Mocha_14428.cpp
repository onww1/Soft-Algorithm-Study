/*
 *  BOJ 14428. 수열과 쿼리 16 
 * 
 *  시간 복잡도 : O((N + M) * logN)
 *  공간 복잡도 : O(N)
 * 
 *  수열과 쿼리 15와 비슷한 문제이지만 구간에 대한 최솟값이므로 이와 관련된 함수를 구현해야 했습니다.
 *  구간 합 문제에서처럼 구간에 대해 접근하면서 구간 내의 범위면 그 값을 가져와서 다른 값들과 비교하고,
 *  그 중에서 가장 작은 값을 리턴하면 되는 것입니다.
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

const int SZ = 1 << 17;
int N, M, A[SZ];
pii tree[2 * SZ];

pii init(int node, int start, int end);
void update(int node, int start, int end, int idx, int val);
pii get_min(int node, int start, int end, int left, int right);

int main(int argc, char *argv[]) {
  open();

  N = readInt();
  for (int i = 1; i <= N; ++i) A[i] = readInt();
  init(1, 1, N);

  M = readInt();
  int a, b, c;
  while (M--) {
    a = readInt(), b = readInt(), c = readInt();;
    if (a == 1) {
      update(1, 1, N, b, c);
    } else {
      printf("%d\n", get_min(1, 1, N, b, c).second);
    }
  }
  return 0;
}

// 초기화 함수
pii init(int node, int start, int end) {
  if (start == end) return tree[node] = {A[start], start};
  int mid = (start + end) / 2;
  return tree[node] = min(init(node * 2, start, mid),
                          init(node * 2 + 1, mid + 1, end));
}

// 업데이트 함수
void update(int node, int start, int end, int idx, int val) {
  if (idx < start || end < idx) return;
  if (start == end) {
    tree[node] = {val, idx};
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, val);
  update(node * 2 + 1, mid + 1, end, idx, val);
  tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

// 구간 최솟값을 구하는 함수
pii get_min(int node, int start, int end, int left, int right) {
  if (end < left || right < start) return {INF, INF};
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) / 2;
  return min(get_min(node * 2, start, mid, left, right),
             get_min(node * 2 + 1, mid + 1, end, left, right));
}