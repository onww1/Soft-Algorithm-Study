/*
 *  BOJ 14427. 수열과 쿼리 15 
 * 
 *  시간 복잡도 : O((N + M) * logN)
 *  공간 복잡도 : O(N)
 * 
 *  세그먼트 트리에 구간의 최솟값을 저장하도록 구현하면 풀 수 있는 문제였습니다.
 *  이때, 쿼리에서 최솟값을 출력하는 것이 전 구간에 대한 최솟값이므로 굳이 함수를 구현할 것 없이 
 *  세그먼트 트리의 첫 번째 노드가 전 구간에 대한 값이므로 바로 첫 번째 노드의 값을 출력하면 됐습니다!
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

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

int main(int argc, char *argv[]) {
  N = readInt();
  for (int i = 1; i <= N; ++i) A[i] = readInt();
  init(1, 1, N);

  M = readInt();
  int a, b, c;
  while (M--) {
    a = readInt();
    if (a == 1) {
      b = readInt(), c = readInt();
      update(1, 1, N, b, c);
    } else {
      printf("%d\n", tree[1].second);
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